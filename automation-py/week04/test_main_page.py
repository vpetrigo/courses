from .pages.main_page import MainPage


def test_guest_can_go_to_login_page(browser):
    link = "http://selenium1py.pythonanywhere.com/catalogue/the-shellcoders-handbook_209?promo=midsummer"
    main_page = MainPage(browser, link)
    main_page.open()
    main_page.go_to_login_page()
    main_page.should_be_login_link()
