using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace LinqTest {
    class ApiHostHelper {

        static string class_name = "";

        public static void handle_test() {
            //string xml = "";
            XmlDocument doc = new XmlDocument();
            doc.Load("ApiHost.XML");
            var root = doc.DocumentElement;
            XmlNodeList nodes = root.SelectNodes("/doc/members/member");
            for (int i = 0; i < nodes.Count;i++ ) {
                XmlNode node = nodes[i];
                string ret_str = "";
                var tmp = node.Attributes["name"].Value;
                string name = node.Attributes["name"].Value;
                if (name[0] == 'T') {
                    class_name = name.Substring(2);
                    Console.WriteLine("\n\n"+class_name+"");
                    continue;
                }

                {
                    var names_ = name.Substring(name.LastIndexOf("Controller.")+11);
                    ret_str += 
                        names_
                        .Replace("Arbitrage", "")
                        .Replace(".", "")
                        .Replace("Zork", "")
                        .Replace("System", "")
                        .Replace("Contract", "")
                        .Replace("MyCombination", "")
                        ;
                    ret_str += "\t";
                }
                
                string summary = node.SelectSingleNode("summary").InnerText;
                ret_str += summary.Replace(" ", "").Replace("\n", "").Replace("\t", "").Replace("\r", "");
                ret_str+= "\t";
                List<string> prams = new List<string>();
                XmlNodeList p_nodes = node.SelectNodes("param");
                for (int j = 0; j < p_nodes.Count; j++) {
                    XmlNode p = p_nodes[j];
                    string p_name = p.Attributes["name"].Value;
                    string value = p.InnerText;
                    ret_str += p_name;
                    ret_str += ":";
                    ret_str += value;
                    ret_str += ",";
                }
                Console.WriteLine(ret_str);
            }
            Console.WriteLine("aaa");
        }
    }
}
