The following describes the YaML format used by the scripts for the API specifications:

## File/Folder Structure
* The scripts search for all *.yml files in ./runtime and ./driver folders.
* Each .yml file represents an output source file to be generated.
* The name of the file will be used in the output filename.

## YML Syntax
* Each document in the yml file represents an entry in the output source.
* Every document must have a "type" scalar: {header, macro, typedef, enum, struct, handle, function}
* The order of documents will determine the order in which they appear in the source code.
* All scalars are assumed to be strings.
* There are three tags types for API namespace replacement:
    * "$x" : lower_case
    * "$X" : ALL_CAPS
    * "$Xx": Camel_Case

#### header
* Every file is required to have a header
* A header requires a "desc" scalar to be used as a file description

```yml
type: header
desc: "appears at the top of the file"
```

#### macro
* A macro initiates the creation of a c/c++ preprocessor definition in the source code
* A macro requires the following scalar fields: "desc", "name" and "value"

```yml
type: macro
desc: "A brief description..."
name: "_XYZ" or "_XYZ( params... )"
value: "0"
```

#### typedef
* A typedef initiates the creation of a c/c++ 'typedef' statement in the source code
* A typedef requires the following scalar fields: "desc", "name" and "value"
* A typedef may take the following optional scalar or sequence of scalar fields: "class"

```yml
type: typedef
desc: "A brief description..."
name: pointer_t
value: "void*"
```

#### const
* A const initiates the creation of a c/c++ 'static const' statement in the source code
* A const requires the following scalar fields: "desc", "name", "typename" and "value"
* A typedef may take the following optional scalar or sequence of scalar fields: "class"

```yml
type: const
desc: "A brief description..."
name: foo
typename: "uint32_t"
value: "0"
```

#### enum
* An enum initiates the creation of a c/c++ 'enum' definition in the source code
* An enum requires the following scalar fields: "desc" and "name"
* An enum may take the following optional scalar or sequence of scalar fields: "class"
* An enum requires the following sequence of scalars: "etors"
* An etor requires the following scalar fields: "name" and "desc"
* An etor may take the following optional scalar field: "value"

```yml
type: enum
desc: "A brief description..."
name: flags_t
etors:
    - name: flag_value_0
      value: "0"
      desc: "brief description"
    - name: flag_value_1
      desc: "brief description"
```

#### struct
* A struct initiates the creation of a c/c++ 'struct' definition in the source code
* A struct requires the following scalar fields: "desc" and "name"
* A struct may take the following optional scalar or sequence of scalar fields: "class"
* A struct requires the following sequence of scalars: "members"
* A member requires the following scalar fields: "type", "name" and "desc"
* A member may take the following optional scalar fields: "init"
* The scripts only support simple 'struct' definitions: no bitfields, no functions, no constructors, no overloaded operators, etc.

```yml
type: struct
desc: "A brief description..."
name: descriptor_t
members:
    - type: uint32_t
      name: count
      desc: "brief description"
    - type: "const void*"
      name: values
      desc: "brief description"
```

#### handle
* A handle initiates the creation of a c/c++ 'struct' definition in the source code
* A handle is a special-case structure for strongly-typed handles
* A handle requires the following scalar fields: "desc" and "name"
* A handle may take the following optional scalar fields: "class"

```yml
type: handle
desc: "A brief description..."
name: foo_handle_t
class: Foo
```

#### function
* A function initiates the creation of a c/c++ function declaration in the source code
* A function requires the following scalar fields: "desc" and "name"
* A function requires the following sequence of scalars: "params"
* A function may take the following optional scalar or sequence of scalar fields: "class"
* A function may take the following optional scalar fields: "decl"
* A function may take the following optional sequence of sequences: "details", "returns" and "analogue"
* A param requires the following scalars: "type", "name" and "desc"
* A detail may be a scalar or sequence
* A return may be a scalar or sequence
* An analogue must be a scalar

```yml
type: function
desc: "A brief description..."
name: foobar
details: 
    - "A more detailed description."
analogue:
    - another_function
returns:
    - "return_value":
        - "brief detail"
    - "another_return_value"
params:
    - type: uint32_t
      name: value
      desc: "brief description"
```

#### class
* A class initiates the creation of a c++ class declaration in the source code
* A class requires the following scalar fields: "desc" and "name"
* A class requires the following sequence of scalars: "members"
* A member requires the following scalar fields: "type", "name" and "desc"

```yml
type: class
desc: "A brief description..."
name: spam_t
members:
    - type: handle_t
      name: handle
      desc: "brief description"
```

