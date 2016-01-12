
1.  枚举的名称全数暴露于一般范围中
    好比 enum Side{ Right, Left }; 和 enum Thing{ Wrong, Right }; 不能一起使用
    C++11 引进了一种特别的 "枚举类"，可以避免上述的问题。使用 enum class 的语法来声明：

    enum class Enumeration
    {
      Val1,
      Val2,
      Val3 = 100,
      Val4 /* = 101 */,
    };
    此种枚举为类型安全的。枚举类型不能隐式地转换为整数；也无法与整数数值做比较。 (表示式 Enumeration::Val4 == 101 会触发编译期错误)

2. enum class Enum2 : unsigned int {Val1, Val2};
    枚举类型的语汇范围(scoping)定义于枚举类型的名称范围中。 使用枚举类型的枚举名时，必须明确指定其所属范围。 
    由前述枚举类型 Enum2 为例，Enum2::Val1是有意义的表示法， 而单独的 Val1 则否

3. 此外，C++11 允许为传统的枚举指定使用类型：

    enum Enum3 : unsigned long {Val1 = 1, Val2};
    枚举名 Val1 定义于 Enum3 的枚举范围中(Enum3::Val1)，但为了兼容性， Val1 仍然可以于一般的范围中单独使用。
