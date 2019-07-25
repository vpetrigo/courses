from .base_page import BasePage
from .locators import CartPageLocators


class CartPage(BasePage):
    def should_be_empty(self):
        self.is_not_element_present(*CartPageLocators.CART_ELEMENT)

    def should_contain_empty_text(self):
        empty_text = "Your basket is empty"
        assert self.is_element_present(
            *CartPageLocators.BASKET_EMPTY_TEXT_ELEMENT
        ), "Cart empty warning element is not present on the page"
        assert self.is_text_present(
            *CartPageLocators.BASKET_EMPTY_TEXT_ELEMENT, empty_text
        ), f"The text '{empty_text}' is not present in the empty basket warning element"
