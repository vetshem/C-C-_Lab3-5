#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/types.h>

MODULE_AUTHOR("Shemchuk Vitalii IO-13 vetshem69@gmail.com");
MODULE_DESCRIPTION("Lab 4.2, using struct list_head");
MODULE_LICENSE("MIT");
#define LIST_LEN 10
#define MSG_PREF "TEST: "

#define print_msg(msg, ...) printk(KERN_ERR MSG_PREF msg, ##__VA_ARGS__);
typedef struct {
  struct list_head lnode;
  int32_t val;
} int_node_t;
// Макрос звільнення пам'яті
// do {}while(0)
#define ilfree(list_head)                                                      \
  do {                                                                         \
    int_node_t *__ptr, *__tmp;                                                 \
    list_for_each_entry_safe(__ptr, __tmp, (list_head), lnode) {               \
      kfree(__ptr);                                                            \
    }                                                                          \
  } while (0)
// макрос Виводу значень до консоли
#define ilprint(list_head)                                                     \
  do {                                                                         \
    int_node_t *__ptr;                                                         \
    print_msg("List: {");                                                      \
    list_for_each_entry(__ptr, (list_head), lnode) {                           \
      printk(KERN_ERR "\t%i ", __ptr->val);                                    \
    }                                                                          \
    printk(KERN_ERR "}\n");                                                    \
  } while (0)
// Ініціалізація списку
// https://elixir.bootlin.com/linux/latest/source/include/linux/list.h#L714
static struct list_head int_list = LIST_HEAD_INIT(int_list);
//Функція для інвертування значень списку

static void task(void) {

  int_node_t *ptr;
  list_for_each_entry(ptr, &int_list, lnode)
	{
			ptr->val = ~ptr->val + 1;
			//ptr->val = -ptr->val;
}
}



static int __init list_module_init(void) {
  int i;
  int ret = 0;
  print_msg("List allocation start...\n");
  // Виділення памяті під елементи списку
  for (i = 0; i < LIST_LEN; ++i) {
    int_node_t *ptr = (int_node_t *)kmalloc(sizeof(*ptr), GFP_KERNEL);
    if (!ptr) {
      print_msg("Can't alloc memory\n");
      ret = -ENOMEM;
      goto alloc_err;
    }
    // Функція для роботи
    get_random_bytes(&ptr->val, sizeof(ptr->val));
    list_add_tail(&ptr->lnode, &int_list);
  }

  print_msg("List allocation finish\n");
  ilprint(&int_list);
  task();

	ilprint(&int_list);

  return 0;
alloc_err:
  ilfree(&int_list);
  return ret;
}
static void __exit list_module_exit(void) {
  ilfree(&int_list);
  print_msg("Hasta la vista, Kernel!\n");
}
module_init(list_module_init);
module_exit(list_module_exit);
