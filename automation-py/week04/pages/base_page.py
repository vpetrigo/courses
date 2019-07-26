from .locators import BasePageLocators

import math
from typing import Sequence
from selenium.webdriver import Remote
from selenium.common.exceptions import NoSuchElementException
from selenium.common.exceptions import NoAlertPresentException
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions as ExpCond


class BasePage:
    def __init__(self, browser: Remote, url: str) -> None:
        """Base class for the web page

        :param selenium.webdriver.Remote browser: Selenium WebDriver instance
        :param str url: Link to the page
        """
        super().__init__()
        self.browser = browser
        self.url = url

    def open(self) -> None:
        """Open the given web page in the browser

        :return: None
        """
        self.browser.get(self.url)

    def is_element_present(self, how: str, what: str, timeout=4) -> bool:
        """

        :param how:
        :param what:
        :param timeout:
        :return:
        """
        try:
            WebDriverWait(self.browser, timeout).until(
                ExpCond.presence_of_element_located((how, what)))
        except TimeoutException:
            return False

        return True

    def is_text_present(self, how: str, what: str, text: str) -> bool:
        return text in self.browser.find_element(how, what).text

    def is_not_element_present(self, how, what, timeout=4):
        try:
            WebDriverWait(self.browser, timeout).until(
                ExpCond.presence_of_element_located((how, what)))
        except TimeoutException:
            return True

        return False

    def is_disappeared(self, how, what, timeout=4):
        try:
            WebDriverWait(self.browser, timeout, 1,
                          TimeoutException).until_not(
                              ExpCond.presence_of_element_located((how, what)))
        except TimeoutException:
            return False

        return True

    def solve_quiz_and_get_code(self) -> None:
        alert = self.browser.switch_to.alert
        x = alert.text.split(" ")[2]
        answer = str(math.log(abs((12 * math.sin(float(x))))))
        alert.send_keys(answer)
        alert.accept()
        try:
            alert = self.browser.switch_to.alert
            print(f"Your code: {alert.text}")
            alert.accept()
        except NoAlertPresentException:
            print("No second alert presented")

    def go_to_login_page(self):
        self._move_to_page(BasePageLocators.LOGIN_LINK)

    def go_to_cart_page(self):
        self._move_to_page(BasePageLocators.CART_BUTTON)

    def should_be_authorized_user(self):
        assert self.is_element_present(
            *BasePageLocators.USER_ICON
        ), "User icon is not presented, probably unauthorised user"

    def should_be_login_link(self):
        assert self.is_element_present(
            *BasePageLocators.LOGIN_LINK), "Login link is not presented"

    def _move_to_page(self, selector: Sequence[str]) -> None:
        link = self.browser.find_element(*selector)
        link.click()
