import pytest
from selenium import webdriver
from selenium.webdriver.chrome.options import Options


def pytest_addoption(parser):
    parser.addoption("--language",
                     action="store",
                     default=None,
                     help="Choose language")


@pytest.fixture(scope="function")
def browser(request):
    print(
        f"Run Chrome browser with {request.config.getoption('language')} language"
    )
    options = Options()
    options.add_argument(f"--lang={request.config.getoption('language')}")
    browser = webdriver.Chrome(options=options)

    yield browser

    browser.quit()
