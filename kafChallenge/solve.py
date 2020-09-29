import pykd
from time import sleep

"""
.load "C:/Users/Software Dev PC/Desktop/x86/pykd.dll"
!py -3.7 -g "C:/Users/Software Dev PC/source/repos/Kaf-Challenge/solve.py"
"""

shellcodeAddress = 0x407000
flagLength = 0x23

flag = ['a' for i in range(flagLength)]

lengthInstruction = """push    ebp
mov     ebp,esp
sub     esp,0Ch
call    dword ptr [kafChallenge!_imp____p___argv (00404130)]
push    4
pop     ecx
shl     ecx,0
mov     eax,dword ptr [eax]
mov     eax,dword ptr [ecx+eax]
mov     dword ptr [ebp-4],eax
push    dword ptr [ebp-4]
call    kafChallenge!strlen (004032df)
pop     ecx
mov     dword ptr [ebp-8],eax
mov     dword ptr [ebp-0Ch],23h
cmp     dword ptr [ebp-8],23h
je      kafChallenge!byteShellcode+0x6 (00407006)"""


DEBUG = False


class solve_chal:
	def acquire_next_instruction(self):
		# 											v Length of `pop eax` instruction
		if DEBUG:
			print("Entered breakpoint...")
		currentInstructionAddr = shellcodeAddress + 1 
		instruction = pykd.dbgCommand(f"u {hex(currentInstructionAddr)} {hex(currentInstructionAddr)}")
		instruction = instruction.strip().split('\n')[-1]
		instruction = instruction[instruction.find(" ") + 1:]
		instruction = instruction[instruction.find(" ") + 1:].strip()

		if DEBUG:
			print(f"Current instruction: {instruction}")
		if len(self.instruction_list) == 0 or self.instruction_list[-1] != instruction:
			self.instruction_list.append(instruction)
		return pykd.eventResult.Proceed

	def __init__(self):
		self.instruction_list = []
		if DEBUG:
			print("[+] Acquiring assembly code...")
			print(f" [=] Setting breakpoint at {hex(shellcodeAddress)}")
		self.bp = pykd.setBp(shellcodeAddress, self.acquire_next_instruction)
		while True:
			try:
				pykd.go()
			except:
				break

		if DEBUG:
			print("[+] Finished getting assembly!")

		self.instruction_list = self.instruction_list[len(lengthInstruction.split("\n")):]
		# print("\n".join(self.instruction_list))


def get_current_compare(line):
	line = line[:-1] if line[-1] == "h" else line
	end_line_num = int(line.split(",")[-1].strip(), 16)
	
	return end_line_num

def get_current_index(line):
	line = line[:-1] if line[-1] == "h" else line
	end_line_num = int(line.split(",")[-1].strip(), 16)
	if line.startswith("shl"):
		return 1 << end_line_num

	if line.startswith("imul"):
		return end_line_num

	print(f"[Current Index] Couldn't find current instruction: {line}")


def main():
	currentNum = 0
	while True:
		if currentNum >= (flagLength * 8 - 1):
			break
		if currentNum > 0:
			proc = pykd.startProcess(f"\"C:/Users/Software Dev PC/source/repos/Kaf-Challenge/PackAndVirtualize/Debug/kafChallenge.exe\" {''.join(flag)}")

		solverObj = solve_chal()
		
		# print("\n".join(solverObj.instruction_list))

		tempCurNum = currentNum
		for instruction_pack_index in range(currentNum, len(solverObj.instruction_list[::7])):
			if DEBUG:
				print(instruction_pack_index)
			instruction_pack = solverObj.instruction_list[instruction_pack_index * 7:
														 (instruction_pack_index + 1) * 7]
			if instruction_pack[0].startswith("push"):
				print("Reached failure.")
				break
			instruction_pack = instruction_pack[2:]
			if DEBUG:
				print(f"Index: {instruction_pack[0]}")
			index = get_current_index(instruction_pack[0])

			instruction_pack = instruction_pack[3:]
			if DEBUG:
				print(f"And: {instruction_pack[0]}")
			and_num = get_current_compare(instruction_pack[0])

			instruction_pack = instruction_pack[1:]
			if DEBUG:
				print(f"jz: {instruction_pack[0]}")
			jmpEq = instruction_pack[0].startswith("je")
			
			if DEBUG:
				print(f"flag[{index}] & {and_num} {'==' if jmpEq else '!='} 0")

			char_num = ord(flag[index])
			if jmpEq:
				#print(bin((char_num) & 0xff))
				char_num &= (~and_num) & 0xff
				#print(bin((char_num) & 0xff))
				#print(bin((~and_num) & 0xff))
			else:
				char_num |= and_num

			char_num = chr(char_num)
			flag[index] = char_num
			tempCurNum += 1
		currentNum = tempCurNum
		print("".join(flag))
		# sleep(0.5)


if __name__ == "__main__":
	main()