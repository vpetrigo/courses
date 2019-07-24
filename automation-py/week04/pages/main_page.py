from .base_page import BasePage

from selenium.webdriver import Remote


class MainPage(BasePage):
    """Represents the main page

    """

    def __init__(self, browser: Remote, url: str) -> None:
        super().__init__(browser, url)
