from selenium.webdriver import Remote
from selenium.webdriver.support.wait import WebDriverWait
from selenium.common.exceptions import NoSuchElementException


class SeleniumAnswer:
    def __init__(self, remote: Remote, step_link: str,
                 timeout: int = 3) -> None:
        self.link = step_link
        self.remote = remote
        self.timeout = timeout

    def send_answer(self, answer: str):
        def wait_textarea(remote: Remote):
            return remote.find_element_by_css_selector("textarea.textarea")

        def wait_textarea_enabled(remote: Remote):
            return remote.find_element_by_tag_name("textarea").is_enabled()

        def wait_correct(remote: Remote):
            return remote.find_element_by_class_name("correct")

        self.remote.get(self.link)
        WebDriverWait(self.remote, self.timeout).until(wait_textarea)

        try:
            self.remote.find_element_by_class_name("again-btn").click()
            WebDriverWait(self.remote, self.timeout).until(wait_textarea_enabled)
        except NoSuchElementException:
            pass

        self.remote.find_element_by_css_selector("textarea.textarea").send_keys(answer)
        self.remote.find_element_by_class_name("submit-submission").click()

        try:
            WebDriverWait(self.remote, self.timeout).until(wait_correct)
        except NoSuchElementException:
            return False

        return True
