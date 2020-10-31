以下内容写得比较草, 只表示大概意思和流程.




有六个属性值:

inStruct: 表示声明在结构体内, 用于防止初始化, 和添加结构体的符号表.
- type_inh: 继承属性, 在Def, ExtDef, CompSt, Stmt及以下, 表示待声明变量的类型, 待声明的函数类型

- isLvalue: 只有Expr有, 用来表示是否为左值.
- speci: 在pecifier structSpecifier中, 只表示类型名, 在高层的Def会被包装成TypeExpr, 为了给VarDec使用.
- type_syn: 综合属性
  - 在ParamDec, Dec和VarDec之间, 为了让ParamList, Dec能知道每个形参的数组维数, 以便构造结构体和函数形参. 因此让最终的数组类型从下面传上来.
  - 在DefList, ParamList中表示声明的变量(形参)列表, tuple型, 用来构造函数类型, 结构体类型
  - 在Expr, 表示表达式的类型表达式.




- Program
  - attr:
  - todo:
    - initSymbol

- extdeflist
  - a  
  - to:
    
- extdef: 
  - attr: 
  - todo 任意产生式:
    - 获取Specifier的speci, type_inh = wrap(speci)
  - 对于函数定义的产生式:
    - 对于函数, 无需pop形参表
   

- ExtDecList: 任意
  - attr: type_inh
  - todo:
  
- Specifier: 任意
  - attr: speci 
  - todo:
    - 对于int, float, speci = 符号表指针.
    - 对于StructSpecifier, speci = StructSpecifier.speci

- StructSpecifier: 
  - attr: speci
  - todo 长的:
    - 
    - OptTag() 后获得其speci
    - 给deflist.instruct = newTable;
    - DefList()后, DefList.type_syn是声明变量的列表(tuple), 将其wrapStruct后作为此结构体的类型.
    - 将speci的内容填好, insert进表.
  - todo 短的:
    - Tag后获得其speci

- OptTag:
  - speci
  - todo 任意:
    -  applySpeci(... &specifer), 若失败, 输出错误信息16

- Tag:
  -  speci
  - todo:
    - lookup(), 看是否有结果, (报错17), 获得符号表项指针, 
    - 检查是其var_speci, 是类型名还是变量名(报错17). speci = 该表项.
  
- VarDec
  - type_inh
  - todo:
    -  appendVar(cur) , 若append失败, 报错3.
    - 对于VarDec[INT], VarDec.type_inh = wrapArray(父亲.type_inh, ..), 递归VarDec.
      - VarDec()后 type_syn = VarDec.type_syn //表示id最终的类型(一般是数组), 为了ParamDec能获取, 我没想到更好的办法了.

- FunDec: 
  - type_inh
  - todo:
    - 继承type_inh
    - 先开表, ParamList()后, 把伪表头删掉, 获得其type_syn, wrapFun(形参, type_inh作返回值), 向全局函数表appendVar(), 若失败, 输出错误4

- ParamList:
  - type_syn(指所有形参, 元组)
  - todo: 
    - 对于ParamList: ParamDec: type.syn = wrapTuple(ParamDec.type_syn, ParamList.type_syn)
    - 对于ParamList: ParamDec COMMA ParamList: wrapTuple(ParamDec.type_syn, NULL)

- ParamDec:
  - type_syn(单个形参)
  - todo:
    - Specifier()后, 获取其speci, type_inh = wrap(speci).
    - VarDec(), type_syn

- CompSt:
  - type_inh(函数返回值类型), 
  - todo:
    - 开新表
    - 最后pop(symbols)

- StmtList:
  - type_inh(函数返回值)
  - todo:
    - 继承
- DefList:
  -  inStruct, type_syn(当inStruct有效时才有效)
  - todo:
    - 若inStruct, 在Def(), DefList()后, catTuple(Def.type_syn, DefList.type_syn)把Def中的声明变量和DefList中的声明变量拼接在一起.

- Def
  - inStruct, type_syn(声明变量的元组)
  - todo:
    - Specifier()后, 获得Specifier.speci, type_inh = wrap(Specifier.speci)
    - type_syn = DecList.type_syn
  
- DecList: 
  - inStruct, type_inh(声明变量类型名), , type_syn(声明变量列表)
  - todo:
    - 对于DecList: Dec, wrapTuple(Dec.type_syn, NULL)
    - 对于DecList: Dec COMMA DecList wrapTuple(Dec.type_syn, DecList)
    - 应该要和ParamList的行为一致.
  
- Dec:
  - inStruct, type_inh(), , type_syn(声明变量的实际类型:可能是个数组)
  - todo:
    - type_syn = VarDec.type_syn
    - 对于VarDec = Exp, 检查VarDec.type_syn 和 Exp.type_syn是否等价.
    - 当inStruct, 检查产生式.
  


- 