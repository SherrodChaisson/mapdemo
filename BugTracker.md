![image-20240402103247707](C:\Users\SHERRIOD\AppData\Roaming\Typora\typora-user-images\image-20240402103247707.png)

```c++
    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
```

* 若第二条语句输出false 安装对应版本的openssl (实验失败)
* 直接把https改为http

![image-20240402165228004](C:\Users\SHERRIOD\AppData\Roaming\Typora\typora-user-images\image-20240402165228004.png)

![image-20240402165238962](C:\Users\SHERRIOD\AppData\Roaming\Typora\typora-user-images\image-20240402165238962.png)

* 使用qvector 崩溃

![image-20240402172432361](C:\Users\SHERRIOD\AppData\Roaming\Typora\typora-user-images\image-20240402172432361.png)

![image-20240402175304483](C:\Users\SHERRIOD\AppData\Roaming\Typora\typora-user-images\image-20240402175304483.png)

* 通过反复比较确认 这不是qvector导致的，而是在构造函数中没有对ui进行初始化，导致访问了野指针。
* 原博客里的确没有进行初始化，不知是作者有意为之还是仅仅是个bug
* 但是令人费解的是 为什么之前没有使用qvector时代码没有崩溃。