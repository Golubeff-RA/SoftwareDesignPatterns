#pragma once
#include <initializer_list>
#include <iomanip>
#include <list>
#include <memory>
#include <ostream>

class INumberSeq {
public:
    virtual int GiveFirst() const = 0;
    virtual int GiveSecond() const = 0;
    virtual int GiveNext(int current, int prev) const = 0;
    void PrintFirstNNums(size_t n, std::ostream& out) const {
        out << std::setw(5);
        if (n == 0) {
            return;
        }

        if (n == 1) {
            out << GiveFirst();
            return;
        }

        int prev = GiveFirst();
        int curr = GiveSecond();
        out << std::setw(5) << prev << " ";
        for (size_t i = 0; i < n; ++i) {
            out << std::setw(5) << curr << " ";
            int temp = curr;
            curr = GiveNext(curr, prev);
            prev = temp;
        }
    }
    virtual ~INumberSeq() = default;
};

using NumberSeqPtr = std::shared_ptr<INumberSeq>;

class FibonacciSeq : public INumberSeq {
public:
    int GiveFirst() const override { return 0; }

    int GiveSecond() const override { return 1; }

    int GiveNext(int current, int prev) const override {
        return current + prev;
    }
};

class EulerSeq : public INumberSeq {
public:
    int GiveFirst() const override { return 1; }

    int GiveSecond() const override { return 1; }

    int GiveNext(int current, int prev) const override {
        return current + prev + 1;
    }
};

class NegativeDecorator : public INumberSeq {
public:
    NegativeDecorator(NumberSeqPtr seq) : seq_(seq) {}

    int GiveFirst() const override { return -seq_->GiveFirst(); }

    int GiveSecond() const override { return -seq_->GiveSecond(); }

    int GiveNext(int current, int prev) const override {
        return -seq_->GiveNext(-current, -prev);
    }

private:
    NumberSeqPtr seq_;
};

class SumOfSeqs : public INumberSeq {
public:
    SumOfSeqs(std::initializer_list<NumberSeqPtr> seqs) {
        for (auto seq : seqs) {
            seqs_.push_back({seq, {seq->GiveSecond(), seq->GiveFirst()}});
        }
    }
    int GiveFirst() const override {
        int sum = 0;
        for (auto seq : seqs_) {
            sum += seq.first->GiveFirst();
        }
        return sum;
    }

    int GiveSecond() const override {
        int sum = 0;
        for (auto seq : seqs_) {
            sum += seq.first->GiveSecond();
        }
        return sum;
    }

    int GiveNext(int, int) const override {
        int sum = 0;
        for (auto& seq : seqs_) {
            int new_curr =
                seq.first->GiveNext(seq.second.current, seq.second.prev);
            sum += new_curr;
            seq.second.prev = seq.second.current;
            seq.second.current = new_curr;
        }
        return sum;
    }

private:
    struct State {
        int current;
        int prev;
    };
    mutable std::list<std::pair<NumberSeqPtr, State>> seqs_;
};
