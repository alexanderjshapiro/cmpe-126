# Lab 3: Last In/First Out, First In/Last Out # 
**10 points**

For this lab, you will be implementing both a *Last In/First Out* and *First In/First Out* data structures. These data structures store data in a way that allows you to only see one value from the structure. You can't see any other value in the structure unless it is the front value.
These structures are important because they allow us to add or remove data members to the structure in an O(1) complexity.

### Lab Instructions
Implement each of the functions to perform the necessary actions outlined in the `.h` files.

As you are writing your functions, read the instructions and think of how you would test that functions while you are writing it. Write your Test first and then implement your functions. Try running your test and then fixing your issues.  

`stack` and `StringVectorQueue` will both be statically sized, meaning that you don't need to worry about dynamically growing the StringVector. Treat it just like an array.
#### Fifo ####
**Queue()**: Default constructor. Set index properly and reserve 100 spaces in StringVectorQueue

**explicit Queue(std::string input_string)**: Constructor that does the same thing as the default constructor, but adds a single item to the Fifo

**Queue(const Queue &original)**: Copy constructor

**virtual Queuee()**: Destructor

**Queue &operator=(const Queue &right)**: Assignment operator

**bool empty() const**: Return true if the Queue is empty and false if it is not

**unsigned size() const**: Return the size of the Queue

**std::string front() const**: Return the front string of the Queue.

**void enqueue(std::string input)**: Add input string to the back of the Queue

**void dequeue()**: Remove the front string from the Queue
#### Lifo ####
**StringVectorStack()**: Default constructor. Set index properly and reserve 100 spaces in StringVectorQueue

**explicit StringVectorStack(std::string input_string)**: Constructor that does the same thing as the default constructor, but adds a single item to the Fifo

**StringVectorStack(const StringVectorStack &original)**: Copy constructor

**virtual Stackk()**: Destructor

**StringVectorStack &operator=(const StringVectorStack &right)**: Assignment operator

**bool empty() const**: Return true if the StringVectorStack is empty and false if it is not

**unsigned size() const**: Return the size of the StringVectorStack

**std::string front() const**: Return the front of the StringVectorStack.

**void push(std::string input)**: Add input string to the front of the string

**void pop()**: Remove the front string from the StringVectorStack


### Hints ###
- Wikipedia article on [Fifo](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)_)
- Wikipedia article on [Lifo](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))
- Some of these functions are basically the same. Don't rewrite or paste code, just call the function with the altered inputs.
- Keep track of your edge cases: empty, 1 item, 2 items
