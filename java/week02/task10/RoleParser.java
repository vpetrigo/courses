/**
 * This class should be compiler with -encoding utf8 flag
 */
import java.util.Arrays;

public class RoleParser {
    private static String printTextPerRole(String[] roles, String[] textLines) {
        StringBuilder[] textPerRole = new StringBuilder[roles.length];

        for (int i = 0; i < roles.length; ++i) {
            textPerRole[i] = new StringBuilder(roles[i] + ":\n");
        }

        for (int line = 0; line < textLines.length; ++line) {
            String[] s = textLines[line].split(":", 2);

            for (int role = 0; role < roles.length; ++role) {
                if (s[0].equals(roles[role])) {
                    textPerRole[role].append(String.valueOf(line + 1) + ")" + s[1] + "\n");
                    break;
                }
            }
        }

        return String.join("\n", textPerRole);
    }

    private static void test() {
        String[] roles = {
            "Городничий", "Аммос Федорович",
            "Артемий Филиппович", "Лука Лукич"
        };
        String[] textLines = {
            "Городничий: Я пригласил вас, господа, с тем, чтобы сообщить вам пренеприятное известие: к нам едет ревизор.",
            "Аммос Федорович: Как ревизор?",
            "Артемий Филиппович: Как ревизор?",
            "Городничий: Ревизор из Петербурга, инкогнито. И еще с секретным предписаньем.",
            "Аммос Федорович: Вот те на!",
            "Артемий Филиппович: Вот не было заботы, так подай!",
            "Лука Лукич: Господи боже! еще и с секретным предписаньем!"
        };

        System.out.print(printTextPerRole(roles, textLines));
    }

    public static void main(String... args) {
        test();
    }
}