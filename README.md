# chunk_sha2
基于SHA256的文件分割与完整性验证系统

### 主要技术：

- C
- OpenSSL

### 开发工具：

- VS Code

### 项目背景：

在数据存储和传输过程中，文件的完整性验证非常重要。为了保证文件在分割和传输过程中不被篡改或损坏，本项目实现了一个基于 SHA256 算法的文件分割与完整性验证系统。该系统能够将大文件分割成多个小文件，并为每个文件生成 SHA256 哈希值，以便后续的完整性验证。

### 项目描述：

该系统通过 C 语言和 OpenSSL 库实现了文件分割和完整性验证功能。系统分为两个主要模块：文件分割和哈希值生成与验证。核心功能包括：

##### 文件分割：

将大文件按照指定大小分割成多个小文件，以便更好地管理和传输。每个小文件的大小可以根据需要进行配置，支持将文件分割成多个部分。

##### 哈希值生成与验证：

为每个分割出的文件生成 SHA256 哈希值，并将这些哈希值保存到一个单独的文件中。在文件传输完成后，通过对比哈希值，验证文件是否在传输过程中被篡改或损坏。

##### 技术细节：

- **文件操作**：使用 `fopen`、`fread`、`fwrite` 等函数实现文件的分割和读取操作。
- **哈希计算**：利用 OpenSSL 库的 `SHA256` 算法生成文件的哈希值，并通过对比哈希值实现完整性验证。
- **存储与对比**：将哈希值保存到文件中，并在接收端对比文件的哈希值，确保文件的完整性和正确性。

该系统通过对文件分割和完整性验证的双重保障，确保了文件在存储和传输过程中的安全性和可靠性。
