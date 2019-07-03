from .base_page import BasePage
from .locators import MainPageLocators


class MainPage(BasePage):
    """Represents the main page

    """

    def go_to_login_page(self) -> None:
        """Go to the login page

        :return: None
        """
        link = self.browser.find_element(*MainPageLocators.REGISTRATION_LINK)
        link.click()

    def should_be_login_link(self) -> None:
        """Find the login link on the main page

        :return: None
        """
        assert self.is_element_present(
            *MainPageLocators.LOGIN_LINK), "No login link on the main page"
