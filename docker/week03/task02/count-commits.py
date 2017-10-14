#!/usr/bin/env python3

import asyncio
import requests
import datetime

API_URL = "https://api.github.com"
COMMITS_URL = "/repos/{}/{}/commits"

with open("token.txt") as token:
        TOKEN = token.readline().strip()

HEADERS = {
    "Accept": "application/vnd.github.v3+json",
    "Authorization": "token " + TOKEN
}


def get_repos(filename: str) -> tuple:
    with open(filename) as repos_f:
        reader = (line.strip().split("/") for line in repos_f)

        for repo in reader:
            yield (repo[-2], repo[-1])


def get_last_page(link_header: str):
    last_page = int(link_header[link_header.rfind("page=") + len("page="):
                                link_header.rfind(">")])

    if last_page == 1:
        last_page += 1

    return last_page


async def process_rest_pages(url: str, page: int, params: dict):
    params["page"] = page
    resp = requests.get(url, params=params, headers=HEADERS)

    if resp.status_code == 200:
        return len(resp.json())


async def count_commits(user: str, repo: str, **kwargs) -> int:
    url = API_URL + COMMITS_URL.format(user, repo)
    params = {"since": kwargs["since"], "until": kwargs["until"], "sha": "master"}
    resp = requests.get(url, params=params, headers=HEADERS)
    commits_num = 0

    if resp.status_code == 200:
        commits_num += len(resp.json())
        link_header = resp.headers.get("Link")

        if link_header:
            tasks = [
                process_rest_pages(url, i, params)
                for i in range(2, get_last_page(link_header) + 1)
            ]

            if len(tasks) > 0:
                done, pending = await asyncio.wait(tasks)
                commits_num += sum(t.result() for t in done)
    else:
        print(url, resp)

    return commits_num


async def main():
    since = datetime.datetime(2016, 1, 1).isoformat()
    until = datetime.datetime(
        2016, 12, 31, hour=23, minute=59, second=00).isoformat()
    tasks = [
        count_commits(*repo_info, since=since, until=until)
        for repo_info in get_repos("repos.txt")
    ]

    done, pending = await asyncio.wait(tasks)
    print(sum((t.result() for t in done)))


if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
    loop.close()
