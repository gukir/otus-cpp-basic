#include <iostream>
#include <limits>
#include <cmath>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
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

	const char * name() const override {
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

    const char * name() const override {
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

    const char * name() const override {
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
        m_std = std::sqrt((m_ssum - m_sum * m_sum / m_num) / (m_num - 1));
    }

    double eval() const override {
        return m_std;
    }

    const char * name() const override {
        return "std";
    }

private:
    double m_sum;
    double m_ssum;
    long m_num;
    double m_std;
};

int main() {

    const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
    statistics[1] = new Max{};
    statistics[2] = new Mean{};
    statistics[3] = new Std{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}
