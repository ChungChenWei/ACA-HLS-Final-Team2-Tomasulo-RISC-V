#include "reservation_stations.hpp"

Reservation_stations::Reservation_stations (Adders *adders_, Multipliers *multipliers_) {
	adders = adders_;
	multipliers = multipliers_;
}

bool Reservation_stations::__get_valid (op_t op_i, int &index_o) {
	int start, size;
	switch (op_i) {
	case OP_ADD:
	case OP_SUB:
		start = RES_STA_ADD_START_INDEX;
		size = RES_STA_ADD_NUM;
		break;

	case OP_MUL:
	case OP_DIV:
		start = RES_STA_MUL_START_INDEX;
		size = RES_STA_MUL_NUM;
		break;

	default:
		start = 0;
		size = 0;
	}

	for (int i = start; i < start + size; ++i) {
		if (entry[i].valid) {
			index_o = i;
			return true;
		}
	}

	return false;
}

bool Reservation_stations::get_valid (op_t op) {
	int tmp;
	return __get_valid(op, tmp);
}

void Reservation_stations::issue (op_t op, reg_stat_t r1, reg_stat_t r2) {
	int index;
	__get_valid(op, index);
	entry[index].valid = false;
	entry[index].op = op;
	entry[index].r1 = r1;
	entry[index].r2 = r2;
}

void Reservation_stations::try_assign_task () {
	// TODO
}

void Reservation_stations::write_from_CDB (res_sta_symbol_t sym, data_t value) {
	for (int i = 0; i < RES_STA_TOTAL_NUM; ++i) {
		if (entry[i].r1.stat == REG_STAT_SYMBOL && entry[i].r1.value.symbol == sym) {
			entry[i].r1.stat = REG_STAT_SCALAR;
			entry[i].r1.value.scalar = value;
		}
		if (entry[i].r2.stat == REG_STAT_SYMBOL && entry[i].r2.value.symbol == sym) {
			entry[i].r2.stat = REG_STAT_SCALAR;
			entry[i].r2.value.scalar = value;
		}
	}
}
