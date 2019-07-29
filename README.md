# m_object
dynamicaly mutable object for simple serialization

use std file stream to serialize data:

```cpp
std::ofstream fileOutputStream("file.txt");

mobj o = {
  {"first", {1,2,3}},
  {"second", "string"},
  {"third", 3.1415956535898f}
};

fileOutputStream << o << "\n";
fileOutputStream.close();
```

and use readFromFile method to deserialize data:

```cpp
mobj o;
o.readFromFile("file.txt");

try {
  if (o["first"][2] != 3) {
    throw "something went wrong";
  }
} catch(std::string str) {
  std::cout << str << std::endl;
}
```
