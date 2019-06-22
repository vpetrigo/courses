import pytest
import math
import time

from selenium import webdriver
from selenium.webdriver import Remote
from selenium.webdriver.support.wait import WebDriverWait
from selenium.common.exceptions import NoSuchElementException


class TestStepikLessons:
    @pytest.fixture
    def browser(self) -> Remote:
        browser = webdriver.Chrome()
        yield browser
        browser.quit()

    @staticmethod
    def _answer() -> float:
        return math.log(int(time.time()))

    @staticmethod
    def _send_answer(remote: Remote, link: str, answer_to_send: str) -> None:
        def wait_textarea(_remote: Remote):
            return _remote.find_element_by_css_selector("textarea.textarea")

        def wait_textarea_enabled(_remote: Remote):
            return _remote.find_element_by_tag_name("textarea").is_enabled()

        def wait_correct(_remote: Remote):
            return _remote.find_element_by_class_name("correct")

        remote.get(link)
        WebDriverWait(remote, 3).until(wait_textarea)

        try:
            remote.find_element_by_class_name("again-btn").click()
            WebDriverWait(remote, 3).until(wait_textarea_enabled)
        except NoSuchElementException:
            pass

        remote.find_element_by_css_selector("textarea.textarea").send_keys(
            answer_to_send)
        remote.find_element_by_class_name("submit-submission").click()

        try:
            WebDriverWait(remote, 3).until(wait_correct)
            expected = "Correct!"
            result = remote.find_element_by_class_name(
                "smart-hints__hint").text
            assert result == expected, f"{expected} != {result}"
        except NoSuchElementException:
            assert False, "No smart-hints__hint element on the page after submission"

    @pytest.mark.parametrize("lesson_num", [
        "236895", "236896", "236897", "236898", "236899", "236903", "236904",
        "236905"
    ])
    def test_stepik_links(self, lesson_num: str, browser: Remote) -> None:
        link = f"https://stepik.org/lesson/{lesson_num}/step/1"
        self._send_answer(browser, link, str(self._answer()))
