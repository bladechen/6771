// std::vector<std::string> string_split(const std::string& s, const std::string& delim)
// {
//     std::vector<std::string> result;
//     if (delim.empty())
//     {
//         result.push_back(s);
//         return result;
//     }
//     std::string::const_iterator substart = s.begin(), subend;
//     while (true)
//     {
//         subend = std::search(substart, s.end(), delim.begin(), delim.end());
//         std::string temp(substart, subend);
//         if ( !temp.empty())
//         {
//             result.push_back(temp);
//         }
//         if (subend == s.end())
//         {
//             break;
//         }
//         substart = subend + delim.size();
//     }
//     return result;
// }


