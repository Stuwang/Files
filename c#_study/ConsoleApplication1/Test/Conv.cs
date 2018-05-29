using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace Test{
    public class Conv {
        public static String ConvertToChinese(Decimal number) {
            var s = number.ToString("#L#E#D#C#K#E#D#C#J#E#D#C#I#E#D#C#H#E#D#C#G#E#D#C#F#E#D#C#.0B0A");
            var d = Regex.Replace(s,
                @"((?<=-|^)[^1-9]*)|((?'z'0)[0A-E]*((?=[1-9])|(?'-z'(?=[F-L\.]|$))))|((?'b'[F-L])(?'z'0)[0A-L]*((?=[1-9])|(?'-z'(?=[\.]|$))))",
                "${b}${z}");
            var r = Regex.Replace(d, ".", m => "负元空零壹贰叁肆伍陆柒捌玖空空空空空空空分角拾佰仟万亿兆京垓秭穰"[m.Value[0] - '-'].ToString());
            if (r.EndsWith("元"))//这两行是我加的
                r += "整";//感觉我拉低了前边代码的逼格……很惭愧
            return r;
        }

        public static String ConvertToChinese2(Decimal number) {
            var s = number.ToString("#L#E#D#C#K#E#D#C#J#E#D#C#I#E#D#C#H#E#D#C#G#E#D#C#F#E#D#C#.0B0A");
            s = s.Replace("0B0A", "@");
            var d = Regex.Replace(s, @"((?<=-|^)[^1-9]*)|((?'z'0)[0A-E]*((?=[1-9])|(?'-z'(?=[F-L\.]|$))))|((?'b'[F-L])(?'z'0)[0A-L]*((?=[1-9])|(?'-z'(?=[\.]|$))))", "${b}${z}");
            var r = Regex.Replace(d, ".", m => "负元空零壹贰叁肆伍陆柒捌玖空空空空空空整分角拾佰仟万亿兆京垓秭穰"[m.Value[0] - '-'].ToString());
            return r;
        }


        public static string ConvertToChinese_su(decimal number) {
            var format = number.ToString("#L#E#D#C#K#E#D#C#J#E#D#C#I#E#D#C#H#E#D#C#G#E#D#C#F#E#D#C#.0B0A").Replace("0B0A", "@");
            var simplify = Regex.Replace(format, @"((?<=-|^)[^1-9|^-]*)|((?'z'0)[0A-E]*((?=[1-9])|(?'-z'(?=[F-L\.]|$))))|((?'b'[F-L])(?'z'0)[0A-L]*((?=[1-9])|(?'-z'(?=[\.]|$))))", "${b}${z}");
            var result = Regex.Replace(simplify, ".", match => "负元空零壹贰叁肆伍陆柒捌玖空空空空空空整分角拾佰仟万亿兆京垓秭穰"[match.Value[0] - '-'].ToString());
            return result;
        }


        /*
         * 利用正则表达式 把 数字转换为 人民币 大写
         * */
        public static String MyConvertToChinese(int number) {
            var s = number.ToString("#C#B#A#E#C#B#A#D#C#B#A#");
            var r = Regex.Replace(s, ".", c => "零壹贰叁肆伍陆柒捌玖空空空空空空空拾佰仟万亿"[c.Value[0] - '0'].ToString());
            var ret = Regex.Replace(r, "(零[拾佰仟万亿]*)+", "零");
            ret = Regex.Replace(ret, @"[拾佰仟万亿]*(?'b'[零壹贰叁肆伍陆柒捌玖]\.*)", "${b}");
            return ret;
        }

        public static void Test() {
            Console.WriteLine(Regex.Replace("aaaaab", @"(?'a'aaaa)", "${a}"));
            Console.WriteLine(MyConvertToChinese(12340000));

            string str = 
@"
sadasdas
";
            Console.WriteLine(str);            
        }
    }
}
