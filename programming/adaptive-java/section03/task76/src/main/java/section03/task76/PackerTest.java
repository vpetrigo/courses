package section03.task76;

public class PackerTest {
    public static void main(String[] args) {
        GiftBox<Food> foodGiftBox = new GiftBox<>();
        foodGiftBox.put(new Food());
        GiftBox<Cake> cakeGiftBox = new GiftBox<>();
        Packer packer = new Packer();
        GiftBox<Bakery> bakeryGiftBox = new GiftBox<>();

        packer.repackage(foodGiftBox, cakeGiftBox);
        packer.repackage(bakeryGiftBox, cakeGiftBox);
    }
}
