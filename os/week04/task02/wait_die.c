/* Напоминание, как выглядят интерфейсы блокировки и переменной
   состояния.

   ВАЖНО: обратите внимание на функции lock_init и condition_init,
          я не уделял этому внимание в видео, но блокировки и
          переменные состояния нужно инциализировать.
*/

struct lock;
void lock_init(struct lock *lock);
void lock(struct lock *lock);
void unlock(struct lock *lock);

struct condition;
void condition_init(struct condition *cv);
void wait(struct condition *cv, struct lock *lock);
void notify_one(struct condition *cv);
void notify_all(struct condition *cv);



/* Далее следует интерфейс, который вам нужно реализовать.

   ВАЖНО: в шаблоне кода стукрутуры содержат поля, некоторые
          функции уже реализованы и присутсвуют комментарии
          - это не более чем подсказка. Вы можете игнорировать
          комментарии, изменять поля структур и реализации
          функций на ваше усмотрение, при условии, что вы
          сохранили интерфейс.

          Вам нельзя изменять имена структур (wdlock_ctx и
          wdlock), а также имена функций (wdlock_ctx_init,
          wdlock_init, wdlock_lock, wdlock_unlock).
*/

struct wdlock_ctx;

struct wdlock {
    /* wdlock_ctx должен хранить информацию обо всех
       захваченных wdlock-ах, а это поле позволит связать
       wdlock-и в список. */
	struct wdlock *next;

    /* Текущий владелец блокировки - из него мы извлекаем
       timestamp связанный с блокировкой, если блокировка
       свободна, то хранит NULL. */
	const struct wdlock_ctx *owner;

    /* lock и cv могут быть использованы чтобы дождаться
       пока блокировка не освободится либо у нее не сменится
       владелец. */
	struct lock lock;
	struct condition cv;
};


/* Каждый контекст имеет свой уникальный timestamp и хранит
   список захваченных блокировок. */
struct wdlock_ctx {
	unsigned long long timestamp;
	struct wdlock *locks;
};


/* Всегда вызывается перед тем, как использовать контекст.

   ВАЖНО: функция является частью интерфейса - не меняйте
          ее имя и аргументы.
*/
void wdlock_ctx_init(struct wdlock_ctx *ctx)
{
	static atomic_ullong next;

	ctx->timestamp = atomic_fetch_add(&next, 1) + 1;
	ctx->locks = NULL;
}

/* Всегда вызывается перед тем, как использовать блокировку.

   ВАЖНО: функция является частью интерфейса - не меняйте
          ее имя и аргументы.
*/
void wdlock_init(struct wdlock *lock)
{
	lock_init(&lock->lock);
	condition_init(&lock->cv);
	lock->owner = NULL;
}

/* Функция для захвата блокировки l контекстом ctx. Если
   захват блокировки прошел успешно функция должна вернуть
   ненулевое значение. Если же захват блокировки провалился
   из-за проверки timestamp-а, то функция должна вернуть 0.

   Помните, что контекст должен хранить информацию о
   захваченных блокировках, чтобы иметь возможность освободить
   их в функции wdlock_unlock.

   ВАЖНО: функция является частью интерфейса - не меняйте
          ее имя и аргументы.
*/
int wdlock_lock(struct wdlock *l, struct wdlock_ctx *ctx)
{
    // Ваш код здесь
    lock(&l->lock);

    while (l->owner != NULL) {
        if (l->owner->timestamp <= ctx->timestamp)
        {
            unlock(&l->lock);
            return 0;
        }

        wait(&l->cv, &l->lock);
    }

    l->owner = ctx;
    l->next = ctx->locks;
    ctx->locks = l;
    unlock(&l->lock);

    return 1;
}

/* Функция для освбождения всех блокировок, захваченных
   контекстом ctx. При этом может случиться так, что этот
   контекст не владеет ни одной блокировкой, в этом случае
   ничего делать не нужно.

   ВАЖНО: функция является частью интерфейса - не меняйте
          ее имя и аргументы.
*/

void wdlock_unlock(struct wdlock_ctx *ctx)
{
	// Ваш код здесь
    while (ctx->locks != NULL) {
        struct wdlock *tmp = ctx->locks;
        
        lock(&tmp->lock);
        tmp->owner = NULL;
        ctx->locks = tmp->next;
        tmp->next = NULL;
        notify_all(&tmp->cv);
        unlock(&tmp->lock);
    }
}