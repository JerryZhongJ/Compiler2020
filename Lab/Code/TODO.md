以下内容写得比较草, 只表示大概意思和流程.

## 约定
对于每一个非终结符, 使用一个函数来实现其处理, 函数名是形如smProgram(因为Program已经被声明为枚举类型了), 函数参数是父节点.

非终结符A的属性在A()中赋值, 不在其父节点赋值.(和书上不一样) //可商议

我实现基础的函数和表达式, 你实现其他的语法分析.

## 关于语法分析, 我的想法:


有六个属性值:

- cur_sym_table: 当前符号表
- preStackTop: StmtList及其以下不需要.
- type_inh: 继承属性, 在Def, ExtDef, CompSt, Stmt及以下, 表示待声明变量的类型, 待声明的函数类型

- isLvalue: 只有Expr有, 用来表示是否为左值.
- speci: 在pecifier structSpecifier中, 只表示类型名, 在高层的Def会被包装成TypeExpr, 为了给VarDec使用.
- type_syn: 综合属性
  - 在ParamDec, Dec和VarDec之间, 为了让ParamList, Dec能知道每个形参的数组维数, 以便构造结构体和函数形参. 因此让最终的数组类型从下面传上来.
  - 在DefList, ParamList中表示声明的变量(形参)列表, tuple型, 用来构造函数类型, 结构体类型
  - 在Expr, 表示表达式的类型表达式.


List类只继承上面的cur_sym_table和preStackTop, 不会开表. 只有CompSt和StructSpecifier, FunDec可能修改当前符号表.
ExtDef, Def从Specifier获得类型名, 包装成TypeExpr, 随后一直继承下去, 直到变量名ID, 到那就已经知道基本类型和数组维度. 可以检查和append了.

错误恢复?

- Program
  - attr:
    - cur_sym_table
    - preStackTop
  - todo:
    - cur_sym_table = preStackTop = NULL;

- extdeflist
  - a  
    - cur_sym_table
    - preStackTop
  - to:
    
- extdef: 
  - attr: cur_tab, prevST, type_inh, 
  - todo 任意产生式:
    - 继承
    - 获取Specifier的speci, type_inh = wrap(speci)
  - 对于函数定义的产生式:
    - 同上
    - 最最后, pop(当前形参表), 

- ExtDecList: 任意
  - attr: 同extdef
  - todo:
    - 继承3个属性
  
- Specifier: 任意
  - attr: speci 
  - todo:
    - 继承cur, prevST
    - 对于int, float, speci = 符号表指针.
    - 对于StructSpecifier, speci = StructSpecifier.speci

- StructSpecifier: 
  - attr: cur, prevST, speci
  - todo 长的:
    - cur=newTable, prevST = NULL; //DefList将继承它们
    - OptTag() 后获得其speci
    - DefList()后, DefList.type_syn是声明变量的列表(tuple), 将其wrapStruct后作为此结构体的类型.
  - todo 短的:
    - Tag后获得其speci

- OptTag:
  - cur, prevST, speci
  - todo 任意:
    - 继承
    -  applySpeci(... &specifer), 若失败, 输出错误信息16

- Tag:
  - cur, prevST, speci
  - todo:
    - lookup(), 看是否有结果, (报错17), 获得符号表项指针, 
    - 检查是其var_speci, 是类型名还是变量名(报错17). speci = 该表项.
  
- VarDec
  - cur, prev, type_inh
  - todo:
    - 继承cur, prev
    - 对于ID, type_inh = 父亲.type_inh, 判断是否exist(当前形参表), appendVar(cur) , 若append失败, 报错3.
    - 对于VarDec[INT], type_inh = wrapArray(父亲.type_inh, ..), 递归VarDec.
      - VarDec()后 type_syn = VarDec.type_syn //表示id最终的类型(一般是数组), 为了ParamDec能获取, 我没想到更好的办法了.

- FunDec: 
  - cur, prev, type_inh
  - todo:
    - 继承type_inh
    - cur = 当前形参表, prev = NULL
    - ParamList()后, 获得其type_syn, wrapFun(形参, type_inh作返回值), 向全局函数表appendVar(), 若失败, 输出错误4
    - **不要**pop(当前形参表)了

- ParamList:
  - type_syn(指所有形参, 元组), cur, prev
  - todo: 
    - 继承cur, prev //ParamDec将继承, VarDec继承
    - 对于ParamList: ParamDec: type.syn = wrapTuple(ParamDec.type_syn, ParamList.type_syn)
    - 对于ParamList: ParamDec COMMA ParamList: wrapTuple(ParamDec.type_syn, NULL)

- ParamDec:
  - type_syn(单个形参), cur, prev, type_inh
  - todo:
    - 继承cur, prev
    - Specifier()后, 获取其speci, type_inh = wrap(speci).
    - VarDec(), type_inh = VarDec.type_inh

- CompSt:
  - type_inh(函数返回值类型), cur, prev
  - todo:
    - cur=newTable(), prev = 父亲.cur;
    - 最后pop(cur)

- StmtList:
  - type_inh(函数返回值), cur, prev
  - todo:
    - 继承
- DefList:
  -  cur, prev
  - todo:
    - 继承cur, prev
    - 在Def(), DefList()后, catTuple(Def.type_syn, DefList.type_syn)把Def中的声明变量和DefList中的声明变量拼接在一起.

- Def
  - type_inh(声明变量类型), cur, prev, type_syn(声明变量的元组)
  - todo:
    - 继承cur, prev
    - Specifier()后, 获得Specifier.speci, type_inh = wrap(Specifier.speci)
    - type_syn = DecList.type_syn
  
- DecList: 
  - type_inh(声明变量类型名: 如int float 结构体), cur, prev, type_syn(声明变量的元组)
  - todo:
    - 对于DecList: Dec, wrapTuple(Dec.type_syn, NULL)
    - 对于DecList: Dec COMMA DecList wrapTuple(Dec.type_syn, DecList)
    - 应该要和ParamList的行为一致.
  
- Dec:
  - type_inh(), cur, prev, type_syn(声明变量的实际类型:可能是个数组)
  - todo:
    - 继承
    - type_syn = VarDec.type_syn
    - 对于VarDec = Exp, 检查VarDec.type_syn 和 Exp.type_syn是否等价.
  


- 