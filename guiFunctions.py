def get_reg_1(number):																			# Get Register 1
	if number<=255:
		return 0
		
	if number>255 and number<= 65535:
		return 0

	if number>65535 and number<=16777215:
		i = 0
		while number>65535:
		 	number = number - 65536
		 	i = i+1
		return i

def get_reg_2(number):																			# Get Register 2
	if number<=255:
		return 0
		
	if number>255 and number<= 65535:
		i = 0
		while number>255:
		 	number = number - 256
		 	i = i+1
		return i

	if number>65535 and number<=16777215:
		i = 0
		j = 0
		while number>65535:
		 	number = number - 65536
		 	i = i+1
		while number>255:
		 	number = number - 256
		 	j = j+1
		return j

def get_reg_3(number):																			# Get Register 3
	if number<=255:
		return number

	if number>255 and number<= 65535:
		i = 0
		while number>255:
		 	number = number - 256
		 	i = i+1
		return number
		
	if number>65535 and number<=16777215:
		i = 0
		j = 0
		while number>65535:
		 	number = number - 65536
		 	i = i+1
		while number>255:
		 	number = number - 256
		 	j = j+1
		return number

