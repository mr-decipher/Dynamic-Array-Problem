#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define trace_message(a, args...) printf("(%s:%d) " a "\n", __FILE__, __LINE__, ##args)
#define trace() printf("TRACE %s:%d\n", __FILE__, __LINE__)

void assert(const char* message, int success);
void test();

void* list_create();
int list_count(void*);
void list_add(void*, void*);
void* list_get(void*, int);
void list_destroy(void*);
void list_remove(void*, void*);

struct Element
{
  void* value;
  int position;
};

typedef struct Element Element; 

void main()
{
    test();
    printf("Test successful");
}

void assert(const char* message, int success)
{
    if (!success)
    {
        trace_message("%s", message);
        exit(1);
    }
}

void test()
{
    void* list = list_create();
    trace();

    int item1 = 5;
    list_add(list, &item1);
    trace();
  
    assert("Count should be 1.", list_count(list) == 1);
    trace();

    assert("Element 1 should be 5.", *(int*)list_get(list, 1) == 5);
    trace();

    int item2 = 6;
    list_add(list, &item2);
    trace();

    assert("Count should be 2.", list_count(list) == 2);
    trace();

    assert("Element 1 should be 5.", *(int*)list_get(list, 1) == 5);
    trace();

    assert("Element 2 should be 6.", *(int*)list_get(list, 2) == 6);
    trace();

    int item3 = 3;
    list_add(list, &item3);
    trace();

    assert("Count should be 3.", list_count(list) == 3);
    trace();

    assert("Element 1 should be 5.", *(int*)list_get(list, 1) == 5);
    trace();

    assert("Element 2 should be 6.", *(int*)list_get(list, 2) == 6);
    trace();

    assert("Element 3 should be 3.", *(int*)list_get(list, 3) == 3);
    trace();

    int item4 = 8;
    list_add(list, &item4);
    trace();

    assert("Count should be 4.", list_count(list) == 4);
    trace();

    assert("Element 1 should be 5.", *(int*)list_get(list, 1) == 5);
    trace();

    assert("Element 2 should be 6.", *(int*)list_get(list, 2) == 6);
    trace();

    assert("Element 3 should be 3.", *(int*)list_get(list, 3) == 3);
    trace();

    assert("Element 4 should be 8.", *(int*)list_get(list, 4) == 8);
    trace();

    list_remove(list, &item2);
    trace();

    assert("Count should be 3.", list_count(list) == 3);
    trace();

    assert("Element 1 should be 5.", *(int*)list_get(list, 1) == 5);
    trace();

    assert("Element 2 should be 3.", *(int*)list_get(list, 2) == 3);
    trace();

    assert("Element 3 should be 8.", *(int*)list_get(list, 3) == 8);
    trace();

    list_remove(list, &item4);
    trace();

    assert("Count should be 2.", list_count(list) == 2);
    trace();

    assert("Element 1 should be 5.", *(int*)list_get(list, 1) == 5);
    trace();

    assert("Element 2 should be 3.", *(int*)list_get(list, 2) == 3);
    trace();

    int item5 = 57;
    list_add(list, &item5);
    trace();

    assert("Count should be 3.", list_count(list) == 3);
    trace();

    assert("Element 1 should be 5.", *(int*)list_get(list, 1) == 5);
    trace();

    assert("Element 2 should be 3.", *(int*)list_get(list, 2) == 3);
    trace();

    assert("Element 3 should be 57.", *(int*)list_get(list, 3) == 57);
    trace();

    list_remove(list, &item1);
    trace();

    assert("Count should be 2.", list_count(list) == 2);
    trace();

    assert("Element 1 should be 3.", *(int*)list_get(list, 1) == 3);
    trace();

    assert("Element 2 should be 57.", *(int*)list_get(list, 2) == 57);
    trace();

    int* items[100];
    for (int i = 0; i < 100; i++)
    {
        items[i] = malloc(sizeof(int));
        *items[i] = 500500500;

        list_add(list, items[i]);
    }
    trace();

    assert("Count should be 102.", list_count(list) == 102);
    trace();

    assert("Element 1 should be 3.", *(int*)list_get(list, 1) == 3);
    trace();

    assert("Element 2 should be 57.", *(int*)list_get(list, 2) == 57);
    trace();

    assert("Element 50 should be 500500500.", *(int*)list_get(list, 50) == 500500500);
    trace();

    assert("Element 102 should be 500500500.", *(int*)list_get(list, 102) == 500500500);
    trace();

    list_remove(list, &item5);
    trace();
    
    assert("Count should be 101.", list_count(list) == 101);
    trace();

    assert("Element 1 should be 3.", *(int*)list_get(list, 1) == 3);
    trace();

    assert("Element 2 should be 500500500.", *(int*)list_get(list, 2) == 500500500);
    trace();

    assert("Element 50 should be 500500500.", *(int*)list_get(list, 50) == 500500500);
    trace();

    assert("Element 101 should be 500500500.", *(int*)list_get(list, 101) == 500500500);
    trace();

    for (int i = 0; i < 100; i++)
    {
        list_remove(list, items[i]);
        free(items[i]);
    }
    trace();

    assert("Count should be 1.", list_count(list) == 1);
    trace();

    assert("Element 1 should be 3.", *(int*)list_get(list, 1) == 3);
    trace();

    list_remove(list, &item3);
    trace();
    
    assert("Count should be 0.", list_count(list) == 0);
    trace();

    list_add(list, &item1);
    trace();
    
    assert("Count should be 1.", list_count(list) == 1);
    trace();

    assert("Element 1 should be 5.", *(int*)list_get(list, 1) == 5);
    trace();

    list_destroy(list);
    trace();
  }
 
void* list_create()
{
    Element* tip = malloc(sizeof(Element));
    tip->position = -1;
    tip->value = NULL;
    
    return tip;
}

void list_add(void* list, void* item)
{
    int count = list_count(list);
    int size = count + 2;

    Element* elements = realloc(list, size * sizeof(Element));
  
    Element* lastElement = &elements[count];
    lastElement->position = count + 1;
    lastElement->value = item;
    
    Element* tip = &elements[count + 1];
    tip->position = -1;
    tip->value = NULL;

}

int list_count(void* list)
{
    int position = 0, length = 0;

    Element* elements = (Element*)list;
    
    for (int i = 0; ; i++)
      {
          position = elements[i].position;
          
          if (position == -1)
          {
            break;
          }
          else 
          {
              length++;
          }
      }

    return length;
}

  void* list_get(void* list, int index)
  {
      int position = index - 1;
      
      Element* elements = (Element*)list;
      
      void* item = elements[position].value;

      return item;  
  }

  void list_destroy(void* list)
  {
      free(list);
  }

  void list_remove(void* list, void* item)
  {
      int count = list_count(list);
      bool itemFound;
      
      Element* elements = (Element*)list;
      
      for (int i = 0; i < count; i++)
      {
          if (elements[i].value == item)
          {
              int position = elements[i].position;
              int steps = count - position + 1;

              Element* tip = &elements[count-1];

              for (int j = 0; j <= steps; j++)
              {
                  Element* currentElement = &elements[position];
                  Element* nextElement = &elements[position+1];
                  
                  void* item = currentElement->value; 
                  
                  currentElement->value = nextElement->value;
                  nextElement->value = item;
                  
                  position++;
              }

              tip->position = -1;
              itemFound = true;
        }
    }

    if (itemFound)
    {
        list = realloc(list, count - 1);
    }
    else 
    {
      printf("\nItem does not exist in the list");
    }

  }