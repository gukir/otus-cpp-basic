#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>
#include <memory>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
    virtual std::string name() const = 0;
};

class Min : public IStatistics {
public:
    Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

    std::string name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
    Max() : m_max{std::numeric_limits<double>::lowest()} {
    }

    void update(double next) override {
        if (next > m_max) {
            m_max = next;
        }
    }

    double eval() const override {
        return m_max;
    }

    std::string name() const override {
        return "max";
    }

private:
    double m_max;
};

class Mean : public IStatistics {
public:
    Mean() : m_sum{0.}, m_num{0}, m_mean{0.} {
    }

    void update(double next) override {
        m_sum += next;
        m_num++;
        m_mean = m_sum / m_num;
    }

    double eval() const override {
        return m_mean;
    }

    std::string name() const override {
        return "mean";
    }

private:
    double m_sum;
    long m_num;
    double m_mean;
};

class Std : public IStatistics {
public:
    Std() : m_sum{0.}, m_ssum{0.}, m_num{0}, m_std{0.} {
    }

    void update(double next) override {
        m_sum += next;
        m_ssum += next*next;
        m_num++;
        if(m_num > 1){
            m_std = std::sqrt((m_ssum - m_sum * m_sum / m_num) / (m_num - 1));
        }
    }

    double eval() const override {
        return m_std;
    }

    std::string name() const override {
        return "std";
    }

private:
    double m_sum;
    double m_ssum;
    long m_num;
    double m_std;
};

class Pct : public IStatistics {
public:
    Pct() : perc{0.}, arr{} {
    }

    Pct(double p){
        if((p < 0.) || (p > 100.)){
            throw std::invalid_argument("Перцентиль должен находиться в диапазоне от 0 до 100");
        }
        perc = p;
    }

    void update(double next) override {
        arr.push_back(next);  
    }

    double eval() const override {
        double index = (perc / 100.) * (arr.size() - 1);
        size_t lower = static_cast<size_t>(std::floor(index));
        size_t upper = static_cast<size_t>(std::ceil(index));

        std::vector<double> copy_arr = arr;
        std::nth_element(copy_arr.begin(), copy_arr.begin() + lower, copy_arr.end());
        double pct = copy_arr[lower];
        if (lower != upper){
            double weight = index - lower;
            std::nth_element(copy_arr.begin(), copy_arr.begin() + upper, copy_arr.end());
            pct = pct * (1. - weight) + copy_arr[upper] * weight;
        }
        return pct;
    }

    std::string name() const override {
        return std::string{"pct"} + std::to_string(static_cast<int>(perc));
    }

private:
    std::vector<double> arr;
    double perc;
};

int main() {
    std::vector<std::unique_ptr<IStatistics>> statistics;

    statistics.push_back(std::make_unique<Min>());
    statistics.push_back(std::make_unique<Max>());
    statistics.push_back(std::make_unique<Mean>());
    statistics.push_back(std::make_unique<Std>());
    statistics.push_back(std::make_unique<Pct>(90.));
    statistics.push_back(std::make_unique<Pct>(95.));

	double val = 0;
	while (std::cin >> val) {
        for (auto& stat : statistics) {
            stat->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
    for (const auto& stat : statistics) {
        std::cout << stat->name() << " = " << stat->eval() << std::endl;
	}

	return 0;
}
