import sys

def my_plus(A, B, sign):
	len_a = len(A)
	len_b = len(B)
	len_m = len_b if len_a < len_b else len_a
	virtual_digit = len_m / 4 + 1
	carry = 0
	result = ''
	result_candidate = ''
	for ii in range(virtual_digit):
		if 4 * (ii + 1) < len_a:
			a = int(A[-4 * (ii + 1) : len_a - 4 * ii])
		elif 4 * ii < len_a:
			a = int(A[: len_a - 4 * ii])
		else:
			a = 0
		if 4 * (ii + 1) < len_b:
			b = int(B[-4 * (ii + 1) : len_b - 4 * ii])
		elif 4 * ii < len_b:
			b = int(B[: len_b - 4 * ii])
		else:
			b = 0
		if sign == '-':
			b = -b
		remain = a + b + carry
		if remain >= 10000:
			remain -= 10000
			carry = 1
		elif remain < 0:
			remain += 10000
			carry = -1
		else:
			carry = 0
		partial_result = '%d' % remain
		if remain != 0:
			result = partial_result + result_candidate
		if ii != virtual_digit -1:
			partial_result_candidate = '%04d' % remain
			result_candidate = partial_result_candidate + result_candidate
	if result == '':
		result = '0'
	return result

def my_multiply(A, B):
	len_a = len(A)
	len_b = len(B)
	virtual_digit_a = len_a / 4 + 2
	virtual_digit_b = len_b / 4 + 1
	carry = 0
	num_result = [0] * (virtual_digit_a + virtual_digit_b)
	for i in range(virtual_digit_b):
		if 4 * (i + 1) < len_b:
			b = int(B[-4 * (i + 1) : len_b - 4 * i])
		elif 4 * i < len_b:
			b = int(B[: len_b - 4 * i])
		else:
			b = 0
		if b == 0:
			continue
		for j in range(virtual_digit_a):
			if 4 * (j + 1) < len_a:
				a = int(A[-4 * (j + 1) : len_a - 4 * j])
			elif 4 * j < len_a:
				a = int(A[: len_a - 4 * j])
			else:
				a = 0
			remain = num_result[i + j] + a * b + carry
			carry = remain / 10000
			remain %= 10000
			num_result[i + j] = remain
		if carry != 0:
			print 'Carry is NOT 0!!!' # Should never reach
	result = ''
	start = False
	for i in reversed(num_result):
		if (not start) and (i == 0):
			continue
		if not start:
			start = True
			result += '%d' % i
		else:
			result += '%04d' % i
	if result == '':
		result = '0'
	return result

def main():
	line = raw_input()
	T = int(line)
	for i in xrange(T):
		line = raw_input()
		if line.find('+') != -1:
			items = line.split('+')
			result = my_plus(items[0], items[1], '+')
			align_len = len(items[1]) + 1
			if align_len < len(result):
				align_len = len(result)
			dash_len = align_len
			print('%*s' % (align_len, items[0]))
			print('%*s' % (align_len, '+' + items[1]))
			print('%*s' % (align_len, '-' * dash_len))
			print('%*s' % (align_len, result))
		elif line.find('-') != -1:
			items = line.split('-')
			result = my_plus(items[0], items[1], '-')
			align_len = dash_len = len(items[1]) + 1
			if align_len < len(items[0]):
				align_len = len(items[0])
			if dash_len < len(result):
				dash_len = len(result)
			print('%*s' % (align_len, items[0]))
			print('%*s' % (align_len, '-' + items[1]))
			print('%*s' % (align_len, '-' * dash_len))
			print('%*s' % (align_len, result))
		elif line.find('*') != -1:
			items = line.split('*')
			result = my_multiply(items[0], items[1])
			align_len = len(result)
			if align_len < len(items[0]):
				align_len = len(items[0])
			if align_len < len(items[1]) + 1:
				align_len = len(items[1]) + 1
			print('%*s' % (align_len, items[0]))
			print('%*s' % (align_len, '*' + items[1]))
			result1 = my_multiply(items[0], items[1][-1:])
			dash_len = len(result1)
			if dash_len < len(items[1]) + 1:
				dash_len = len(items[1]) + 1
			print('%*s' % (align_len, '-' * dash_len))
			print('%*s' % (align_len, result1))
			if len(items[1]) > 1:
				for i in range(1, len(items[1])):
					result1 = my_multiply(items[0], items[1][len(items[1]) - i -1:len(items[1]) - i])
					print('%*s' % (align_len - i, result1))
				dash_len = len(result)
				if dash_len < len(items[1]):
					dash_len = len(items[1])
				print('%*s' % (align_len, '-' * dash_len))
				print('%*s' % (align_len, result))
		print('')
	sys.exit(0)

if __name__ == "__main__":
	main()
