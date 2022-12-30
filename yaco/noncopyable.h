#ifndef __YACO_NOCOPYABLE_H__
#define __YACO_NOCOPYABLE_H__

/**
 * @file noncopyable.h
 * @brief 不可拷贝对象封装
 * @author Lihua
 * @email 2634610614@qq.com
 * @date 2022-12-30
 */

namespace yaco
{

/**
 * @brief 对象无法拷贝,赋值
 */
class Noncopyable
{
public:
    /**
     * @brief 默认构造函数
     */
    Noncopyable() = default;
    /**
     * @brief 默认析构函数
     */
    ~Noncopyable() = default;
    /**
     * @brief 拷贝构造函数(禁用)
     */
    Noncopyable(const Noncopyable&) = delete;
    /**
     * @brief 赋值函数(禁用)
     */
    Noncopyable& operator=(const Noncopyable&) = delete;
}

}

#endif // !__YACO_NOCOPYABLE_H__