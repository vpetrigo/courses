import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.IllegalArgumentException;

public class DeserializeAnimal {
    public static void main(String[] args) throws IOException {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        ObjectOutputStream oos = new ObjectOutputStream(bos);
        Animal a = new Animal("Cat");

        oos.writeInt(2);
        oos.writeObject(a);
        oos.flush();

        try {
            Animal[] arr = deserializeAnimalArray(bos.toByteArray());

            for (Animal anim : arr) {
                System.out.println(anim.equals(a));
            }
        }
        catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
        }
    }

    public static Animal[] deserializeAnimalArray(byte[] data) throws IllegalArgumentException {
        // your implementation here
        ByteArrayInputStream bis = new ByteArrayInputStream(data);
        try (ObjectInputStream ois = new ObjectInputStream(bis)) {
            int size = ois.readInt();
            Animal[] animals = new Animal[size];

            for (int i = 0; i < size; ++i) {
                animals[i] = (Animal) ois.readObject();
            }

            return animals;
        }
        catch (Exception e) {
            throw new IllegalArgumentException(e);
        }
    }
}
