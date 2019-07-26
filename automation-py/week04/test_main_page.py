from .pages.main_page import MainPage
from .pages.login_page import LoginPage
from .pages.cart_page import CartPage

import pytest

main_page_link = "http://selenium1py.pythonanywhere.com"


@pytest.mark.login_guest
class TestLoginFromMainPage:
    def test_guest_can_go_to_login_page(self, browser) -> None:
        main_page = MainPage(browser, main_page_link)
        main_page.open()
        main_page.go_to_login_page()
        main_page.should_be_login_link()
        login_page = LoginPage(browser, browser.current_url)
        login_page.should_be_login_page()

    def test_guest_should_see_login_link(self, browser) -> None:
        main_page = MainPage(browser, main_page_link)
        main_page.open()
        main_page.go_to_cart_page()
        cart_page = CartPage(browser, browser.current_url)
        cart_page.should_be_empty()
        cart_page.should_contain_empty_text()
