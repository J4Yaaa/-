#include <stdio.h>

int MatchCore(char* str,char* partern)
{
    //这种情况是两个字符串都已经走完了,而且匹配
    if(*str == '\0' && *partern == '\0')
    {
        return 1;
    }

    //这种情况是字符串已经走完但是模式没有走完,出现这个情况可能是
    //  a) .* 情况,这里可能会让字符串走一步,模式走两步,所以模式达到结尾,但是字符串没有
    //     因为 .* 可以匹配任何字符串的任何长度,所以这里我们应该回退一下,让字符串走一步但是模式不走
    //  b) a* 情况,这里的a表示和字符串相等的字符,与上面一样,也可能是因为字符串走一步,模式走两步达到了模式的结尾
    //     我们应该回到上一步,让字符串走一步,模式不走
    if(*str != '\0' && *partern == '\0')
    {
        return 0;
    }

    if(*(partern + 1) == '*')
    {
        //这里分析的是   a* 和 .* 的情况
        if(*partern == *str || (*partern == '.' && *str != '\0'))
        {
            return MatchCore(str+1,partern+2)
                || MatchCore(str+1,partern)
                || MatchCore(str,partern+2);  // 这种是常规情况,可以处理大多的 第二个是 * 的情况
        }
        else
        {
            //如果 * 前的字符 和字符串的字符不相等,那么就直接让模式向后走两步,等于舍弃这里这个没用的通配符
            return MatchCore(str,partern+2);
        }
    }

    //处理 . 通配符
    if(*str == *partern || (*partern == '.' && *str != '\0'))
    {
        MatchCore(str+1,partern+1);
    }
    return 0;
}

int IsMatch(char* str,char* partern)
{
    if(str == NULL || partern == NULL)
    {
        return 0;
    }
    return MatchCore(str,partern);
}

void Test()
{
    char str[] = "abcd";
    char partern[] = "a.*c.*";
    int ret = IsMatch(str,partern);
    printf("ret = %d\n",ret);
}

int main()
{
    Test();
    return 0;
}
