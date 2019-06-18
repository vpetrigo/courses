from selenium.webdriver import Remote
from selenium.webdriver.support.wait import WebDriverWait


class SeleniumAuth:
    AUTH_LINK = "https://stepik.org/catalog?auth=login"

    def __init__(self,
                 username: str,
                 password: str,
                 remote: Remote,
                 timeout: int = 3) -> None:
        self.timeout = timeout
        self.username = username
        self.password = password
        self.remote = remote

    def auth(self) -> None:
        self.remote.get(self.AUTH_LINK)
        WebDriverWait(
            self.remote,
            self.timeout).until(lambda x: x.find_element_by_name("login"))
        auth_elems = "login", "password"
        self.remote.find_element_by_name(auth_elems[0]).send_keys(
            self.username)
        self.remote.find_element_by_name(auth_elems[1]).send_keys(
            self.password)
        self.remote.find_element_by_class_name("sign-form__btn").click()
        WebDriverWait(self.remote, self.timeout).until(
            lambda x: x.find_element_by_class_name("navbar__profile-img"))
