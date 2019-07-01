from .base_page import BasePage

from selenium.webdriver.common.by import By
from selenium.webdriver.remote.webelement import WebElement


class MainPage(BasePage):
    """Represents the main page

    """

    def go_to_login_page(self) -> None:
        """Go to the login page

        :return: None
        """
        link = self.browser.find_element(By.CSS_SELECTOR, "#login_link")
        link.click()

    def should_be_login_link(self) -> None:
        """Find the login link on the main page

        :return: None
        """
        assert self.is_element_present(
            By.CSS_SELECTOR, "#login_link"), "No login link on the main page"
