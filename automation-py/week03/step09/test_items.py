from selenium.webdriver import Remote

link = "http://selenium1py.pythonanywhere.com/catalogue/coders-at-work_207/"


def test_add_to_basket_button(browser: Remote) -> None:
    browser.get(link)
    assert browser.find_element_by_class_name(
        "btn-add-to-basket"), "The button for adding to basket does not exist"
