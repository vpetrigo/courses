/* load_linked читает значение из ячейки памяти, на которую
   указывает x, и возвращает прочитанное значение. */
int load_linked(atomic_int *x);

/* store_conditional сохраняет значение new_value в ячейку
   памяти, на которую указывает x, но только при выполнении
   двух условий:
     - ячейка памяти ранее была прочитана с помощью load_linked
     - между последним load_linked для этой ячейки памяти и
       вызовом store_conditional никто не пытался записать
       значение в ячейку памяти
   Функция возвращает true, если значение было успешно записано
   и false в противном случае. */
bool store_conditional(atomic_int *x, int new_value);

/* Следующие две функции - ваше задание. Эти функции нужно
   реализовать используя load_linked и store_conditional для
   обращений к atomic_int */

/* atomic_fetch_add добавляет arg к значению записанному
   на которое указывает x. И возвращает предыдущее значение,
   на которое указывал x, как результат.

   Т. е. если x указывает на значение 3138 и вы вызываете
   atomic_fetch_add с arg == 10, то функция должна изменить
   значение, на которое указывает x на 3148 и вернуть 3138
   в качестве результата. */
int atomic_fetch_add(atomic_int *x, int arg)
{
    /* Ваш код здесь */
    int retval;

    do {
        retval = load_linked(x);
    } while (!store_conditional(x, retval + arg));

    return retval;
}

/* atomic_compare_exchange сравнивает значение, на которое
   указывает x, со значением, на которое указывает expected_value,
   если они равны, то функция должна записать new_value в ячейку,
   на которую указывает x и возвращает true.
   В противном случае, функция должна записать значение, на
   которое указывает x, в ячейку, на которую указывает
   expected_value и вернуть false.

   Т. е. если x указывает на значение 42, expected_value тоже
   указывает на 42, и функция вызывается с new_value == 3148,
   то функция должна записать 3148 в ячейку, на которую указывает
   x, и вернуть true.

   А если x указывает на значение 3148, expected_value указывает
   на значение 42, и new_value == 0, то функция должна записать
   в *expected_value значение 3148 и вернуть false.

   Обратите внимание, что функция должна возвращать false только
   если x хранит значение отличное от *expected_value, а
   store_conditional может верунть false, даже если значение не
   измнилось. */
bool atomic_compare_exchange(atomic_int *x, int *expected_value, int new_value)
{
    /* Ваш код здесь */
    do {
        int value = load_linked(x);

        if (value != *expected_value) {
            *expected_value = value;
            return false;
        }
    } while (!store_conditional(x, new_value));

    return true;
}