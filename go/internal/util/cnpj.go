package util

import "fmt"

const (
	_BASE = 36
	_N    = 12
)

var weight1 = []byte{5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2}
var weight2 = []byte{6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2}

func encode(c byte) byte {
	if c < 'A' {
		return c - '0'
	}
	return c - 'A' + 10
}

func decode(d byte) byte {
	if d < 10 {
		return d + '0'
	}
	return d - 10 + 'A'
}

func dotProduct(v1, v2 []byte) int16 {
	var sum int16 = 0
	for i := 0; i < _N; i++ {
		sum += int16(v1[i]) * int16(v2[i]-'0')
	}
	return sum
}

func calcDv(v []byte) int16 {
	d1 := dotProduct(weight1, v) % 11
	d2 := dotProduct(weight2, v)

	if d1 > 1 {
		d1 = 11 - d1
	} else {
		d1 = 0
	}
	d2 += d1 * int16(weight2[_N])
	d2 %= 11
	if d2 > 1 {
		d2 = 11 - d2
	} else {
		d2 = 0
	}

	return int16(10*d1 + d2)
}

func Encode(cnpj string) uint64 {
	in := []byte(cnpj)
	var code uint64 = 0
	for _, b := range in[:_N] {
		code = code*_BASE + uint64(encode(b))
	}
	return code
}

func Decode(code uint64) string {
	out := make([]byte, _N+2)

	for i := _N - 1; i >= 0; i-- {
		out[i] = decode(byte(code % _BASE))
		code /= _BASE
	}
	dv := calcDv(out)
	out[_N] = byte(dv/10 + '0')
	out[_N+1] = byte(dv%10 + '0')

	return string(out)
}

func RemoveMask(cnpj string) string {
	out := make([]byte, 0, len(cnpj))
	for i := 0; i < len(cnpj); i++ {
		if (cnpj[i] >= '0' && cnpj[i] <= '9') || (cnpj[i] >= 'A' && cnpj[i] <= 'Z') {
			out = append(out, cnpj[i])
		}
	}
	unmaskedCnpj := string(out)
	diff := _N + 2 - len(unmaskedCnpj)
	if diff > 0 {
		unmaskedCnpj = fmt.Sprintf("%014s", unmaskedCnpj)
	}
	return unmaskedCnpj
}

func AddMask(cnpj string) string {
	if len(cnpj) != _N+2 {
		return ""
	}
	return fmt.Sprintf("%s.%s.%s/%s-%s",
		cnpj[:2], cnpj[2:5], cnpj[5:8], cnpj[8:12], cnpj[12:14])
}

func Validate(cnpj string) bool {
	if len(cnpj) != _N+2 {
		return false
	}

	for _, c := range cnpj[:_N] {
		if (c < '0' || c > '9') && (c < 'A' || c > 'Z') {
			return false
		}
	}

	for _, c := range cnpj[_N : _N+2] {
		if c < '0' || c > '9' {
			return false
		}
	}

	dv := int16(10*(cnpj[_N]-'0') + (cnpj[_N+1] - '0'))
	return calcDv([]byte(cnpj)) == dv
}
