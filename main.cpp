#include <bits/stdc++.h>


// immutable class
class BigInteger {
private:
    bool isNegative;
    std::vector<int> num;
public:
    explicit BigInteger(std::string number) {
        if (number[0] == '-') {
            isNegative = true;
            for (size_t i = number.size() - 1; i > 0; i--)
                num.push_back(number[i] - 48);
        } else {
            isNegative = false;
            for (int i = number.size() - 1; i >= 0; i--)
                num.push_back(number[i] - 48);
        }
    }

    BigInteger(bool _isNegative, std::vector<int> _num) : isNegative(_isNegative), num(std::move(_num)) {}

    std::vector<int> getNumber() {
        return num;
    }

    bool isNegate() {
        return isNegative;
    }

    void clearZero() {
        int temp = this->num.size() - 1;
        while(this->num[temp] == 0 && temp > 0) {
            this->num.pop_back();
            temp--;
        }
    }

    BigInteger abs() {
        return {false, this->num};
    }
    void toString() {
        if (this->isNegative)
            std::cout << "-";
        std::vector<int> temp = this->num;
        reverse(temp.begin(), temp.end());
        bool checkZero = false;
        for (auto now : temp) {
            if (now || checkZero) {
                checkZero = true;
                std::cout << now;
            }
        }
        if (!checkZero)
            std::cout << temp.back();
    }

    // a.comparator(b) a > b return 1, a == b return 0, a < b return -1;
    int comparator(BigInteger number) {
        number.clearZero();
        this->clearZero();
        if (!this->isNegative && !number.isNegate()) {
            if (this->num.size() > number.getNumber().size())
                return 1;
            if (this->num.size() < number.getNumber().size())
                return -1;
            if (this->num.size() == number.getNumber().size())
                for (int i = number.getNumber().size() - 1; i >= 0; i--) {
                    if (this->num[i] > number.getNumber()[i])
                        return 1;
                    if (this->num[i] < number.getNumber()[i])
                        return -1;
                }
            return 0;
        }
        if (number.isNegate() ^ this->isNegative) {
            if (number.isNegate())
                return 1;
            else return -1;
        }
        return -BigInteger(!this->isNegative, this->num).comparator(BigInteger(!number.isNegate(), number.getNumber()));
    }

    BigInteger negate() {
        return BigInteger(!this->isNegative, this->num);
    }

    BigInteger add(BigInteger number) {
        std::vector<int> newObject;
        int prev = 0;
        if (!(number.isNegate() ^ this->isNegative)) {
            for (size_t i = 0; i < std::min(number.getNumber().size(), this->num.size()); i++) {
                newObject.push_back((number.getNumber()[i] + this->num[i] + prev) % 10);
                prev = (number.getNumber()[i] + this->num[i] + prev) / 10;
            }
            if (number.getNumber().size() > this->num.size())
                for (size_t i = this->num.size(); i < number.getNumber().size(); i++) {
                    newObject.push_back((number.getNumber()[i] + prev) % 10);
                    prev = (number.getNumber()[i] + prev) / 10;
                }
            else
                for (size_t i = number.getNumber().size(); i < this->num.size(); i++) {
                    newObject.push_back((this->num[i] + prev) % 10);
                    prev = (this->num[i] + prev) / 10;
                }
            if (prev)
                newObject.push_back(prev);
            return BigInteger(number.isNegate(), newObject);
        } else {
            if (!this->isNegative) {
                if (this->comparator(number.negate()) == 0)
                    return BigInteger(true, {0});
                if (this->comparator(number.negate()) == 1) {
                    for (size_t i = 0; i < std::min(number.getNumber().size(), this->num.size()); i++) {
                        if (this->num[i] - number.getNumber()[i] - prev >= 0) {
                            newObject.push_back(this->num[i] - number.getNumber()[i] - prev);
                            prev = 0;
                        } else {
                            newObject.push_back(10 - number.getNumber()[i] + this->num[i] - prev);
                            prev = 1;
                        }
                    }
                    for (size_t i = number.getNumber().size(); i < this->num.size(); i++) {
                        if (this->num[i] - prev >= 0) {
                            newObject.push_back(this->num[i] - prev);
                            prev = 0;
                        } else {
                            newObject.push_back(10 + this->num[i] - prev);
                            prev = 1;
                        }
                    }
                    return BigInteger(false, newObject);
                } else {
                    for (size_t i = 0; i < std::min(number.getNumber().size(), this->num.size()); i++) {
                        if (number.getNumber()[i] - this->num[i] - prev >= 0) {
                            newObject.push_back(number.getNumber()[i] - this->num[i] - prev);
                            prev = 0;
                        } else {
                            newObject.push_back(10 + number.getNumber()[i] - this->num[i] - prev);
                            prev = 1;
                        }
                    }
                    for (size_t i = this->num.size(); i < number.getNumber().size(); i++) {
                        if (number.getNumber()[i] - prev >= 0) {
                            newObject.push_back(number.getNumber()[i] - prev);
                            prev = 0;
                        } else {
                            newObject.push_back(10 + number.getNumber()[i] - prev);
                            prev = 1;
                        }
                    }
                    return BigInteger(true, newObject);
                }
            } else {
                return number.add(BigInteger(this->isNegative, this->num));
            }
        }
    }

    BigInteger subtract(BigInteger number) {
        if (this->comparator(number) == 0)
            return BigInteger(false, {0});
        return this->add(BigInteger(!number.isNegate(), number.getNumber()));
    }

    BigInteger multiply(BigInteger number) {
        BigInteger ans = {false, {0}};
        std::vector<int> temp = this->num;
        for (int i = 0; i < number.getNumber().size(); i++) {
            std::vector<int> newObject;
            int prev = 0;
            for (int j = 0; j < temp.size(); j++) {
                newObject.push_back((prev + temp[j] * number.getNumber()[i]) % 10);
                prev = (prev + temp[j] * number.getNumber()[i]) / 10;
            }
            if (prev)
                newObject.push_back(prev);
            ans = ans.add(BigInteger(false, newObject));
            reverse(temp.begin(), temp.end());
            temp.push_back(0);
            reverse(temp.begin(), temp.end());
        }
        return BigInteger(number.isNegate() ^ this->isNegative, ans.getNumber());
    }

    BigInteger divide(BigInteger number) {
        BigInteger temp = this->abs();
        if (temp.comparator(number) == -1)
            return {false, {0}};
        if (temp.comparator(number.abs()) == 0)
            return BigInteger(number.isNegate() ^ this->isNegative, {1});
        if (number.comparator({false, {0}}) == 0) {
            std::cout << "Divide by zero!";
            throw "Divide by zero";
        }
        BigInteger ans = {false, {0}};
        while (temp.comparator(number) >= 0) {
            bool flag = false;
            for (int i = temp.getNumber().size() - 1; i >= 0; i--) {
                std::vector<int> ranks;
                for (int j = i; j < temp.getNumber().size(); j++) {
                    ranks.push_back(temp.getNumber()[j]);
                }
                for (int k = 9; k > 0; k--) {
                    if (BigInteger(false, ranks).comparator(BigInteger(false, {k}).multiply(number)) >= 0) {
                        flag = true;
                        ranks = BigInteger(false, {k}).multiply(number).getNumber();
                        reverse(ranks.begin(), ranks.end());
                        std::vector<int> newObject;
                        for (int j = 0; j < i; j++) {
                            ranks.push_back(0);
                            newObject.push_back(0);
                        }
                        newObject.push_back(k);
                        ans = ans.add({false, newObject});
                        reverse(ranks.begin(), ranks.end());
                        temp = temp.subtract(BigInteger(false, ranks));
                    }
                    if (flag)
                        break;
                }
                if (flag)
                    break;
            }
        }
        return BigInteger(number.isNegate() ^ this->isNegative, ans.getNumber());
    }

    BigInteger mod(BigInteger number) {
        return this->subtract(number.multiply(this->divide(number)));
    }

    BigInteger sqrt() {
        if (this->comparator({false, {0}}) == -1) {
            std::cout << "Negative root!";
            throw "Negative root";
        }
        if (this->comparator({false, {0}}) == 0 || this->comparator({false, {1}}) == 0)
            return {this->isNegative, this->num};
        BigInteger l = BigInteger(false, {0}); // множество чисел меньше корня
        BigInteger r = BigInteger({false, this->num}); // множество чисел больше корня
        while (r.subtract(l).comparator({false, {1}}) > 0) {
            BigInteger temp = r.subtract(l).divide({false, {2}}).add(l);
            if (temp.multiply(temp).comparator(BigInteger(this->isNegative, this->num)) <= 0)
                l = temp;
            if (temp.multiply(temp).comparator(BigInteger(this->isNegative, this->num)) > 0)
                r = temp;
        }
        return l;
    }
};


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("There was no unexpected error, please try again");
        return 1;
    }
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("Not found input file exception");
        fclose(in);
        return 1;
    }
    std::string s1;
    std::cin >> s1;
    BigInteger(s1).sqrt().toString();
    return 0;
}
