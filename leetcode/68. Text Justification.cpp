// PROBLEM :


Given an array of strings words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line does not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified, and no extra space is inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.
 

Example 1:

Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Example 2:

Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]


// SOLUTION :


class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = words.size();
        int index = 0;

        while (index < n) {
            int totalChars = words[index].length();
            int last = index + 1;

            // Find the last word that fits on the current line
            while (last < n) {
                if (totalChars + 1 + words[last].length() > maxWidth) break;
                totalChars += 1 + words[last].length();
                last++;
            }

            int diff = last - index - 1; // Number of spaces between words
            string line;

            // If it's the last line or there's only one word, left justify
            if (last == n || diff == 0) {
                for (int i = index; i < last; ++i) {
                    line += words[i];
                    if (i < last - 1) line += " ";
                }
                line.append(maxWidth - line.length(), ' ');
            } else {
                int spaceNeeded = maxWidth - totalChars;
                int spaceBetweenWords = spaceNeeded / diff;
                int extraSpaces = spaceNeeded % diff;

                for (int i = index; i < last; ++i) {
                    line += words[i];
                    if (i < last - 1) {
                        int spacesToApply = spaceBetweenWords + ((i - index) < extraSpaces ? 1 : 0);
                        line.append(spacesToApply + 1, ' '); // +1 for default space
                    }
                }
            }

            result.push_back(line);
            index = last;
        }

        return result;
    }
};


