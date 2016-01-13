iostream 标准库支持内存中的输入／输出，只要将流与存储在程序内存中的 string 对象捆绑起来即可。此时，可使用 iostream 输入和输出操作符读写这个 string 对象.
标准库定义了三种类型的字符串流： 
•   istringstream，由 istream 派生而来，提供读 string 的功能。 
•   ostringstream，由 ostream 派生而来，提供写 string 的功能。 
•   stringstream，由 iostream 派生而来，提供读写 string 的功能。 
要使用上述类，必须包含 sstream 头文件