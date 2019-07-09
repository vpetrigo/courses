import math
from selenium.common.exceptions import NoAlertPresentException
from selenium.webdriver import Remote
from selenium.common.exceptions import NoSuchElementException


class BasePage:
    def __init__(self, browser: Remote, url: str) -> None:
        """Base class for the web page

        :param selenium.webdriver.Remote browser: Selenium WebDriver instance
        :param str url: Link to the page
        """
        super().__init__()
        self.browser = browser
        self.url = url
        self.browser.implicitly_wait(10)

    def open(self) -> None:
        """Open the given web page in the browser

        :return: None
        """
        self.browser.get(self.url)

    def is_element_present(self, how: str, what: str) -> bool:
        """

        :param how:
        :param what:
        :return:
        """
        try:
            self.browser.find_element(how, what)
        except NoSuchElementException:
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
