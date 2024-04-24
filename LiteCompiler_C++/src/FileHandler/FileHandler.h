//
// Created by Ice-bubble on 24-4-21.
//

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>

/**
 * @brief FileHandler类，主要用于对文件的输入输出处理
 */
class FileHandler
{
public:
    /**
    * @brief 从指定文件中读取内容并存储到字符串中。
    * @param filename 要读取的文件名
    * @param [out]content 读取的文件内容将被存储在此字符串中
    * @param errorMessage 如果发生错误，将错误消息存储在此字符串中
    * @return bool 如果成功读取文件则返回true，否则返回false
    **/
    static bool readFile(const std::string &filename, std::string &content, std::string &errorMessage);

    /**
    * @brief 写入字符串到指定文件中。
    * @param filename 要写入的文件名
    * @param content 需要写入的文件内容将被存储在此字符串中
    * @param errorMessage 如果发生错误，将错误消息存储在此字符串中
    * @return bool 如果成功写入文件则返回true，否则返回false
    **/
    static bool writeFile(const std::string &filename, const std::string &content, std::string &errorMessage);
};

#endif // FILE_HANDLER_H
