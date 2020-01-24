class Poly:
	def __init__(self,vet,inverse=True):
		self.p = inverse and vet[:] or vet[::-1]
		i=0
		while i<len(self.p) and self.p[i]==0:
			i+=1
		self.p = self.p[i:][::-1]
	def __repr__(self):
		l = len(self)
		return len(self) and ' + '.join([f'{self.p[l-i-1]} x^{l-i-1}' for i in range(len(self.p))]) or '0'
	def __getitem__(self,i):
		if 0<=i < len(self.p):
			return self.p[i]
		return 0
	def __len__(self):
		return len(self.p)
	def __sub__(self,other):
		return Poly([self[i]-other[i] for i in range(max(len(self),len(other)))],False)
	def __add__(self,other):
		return Poly([self[i]+other[i] for i in range(max(len(self),len(other)))],False)
	def __mul__(self,other):
		if isinstance(other,(int,float)):
			return Poly([i*other for i in self.p],False)
		a=[0]*(len(self)+len(other))
		for i in range(len(self)):
			for j in range(len(other)):
				a[i+j] += self[i]*other[j]
		return Poly(a,False)
	
	def __truediv__(self,other):
		ans,num,den = Poly([]), Poly(self.p,False), Poly(other.p,False)
		while len(num)-len(den)>=0:
			divisao = num[len(num)-1]/den[len(den)-1]
			q = Poly([0]*(len(num)-len(den))+[divisao],False)
			ans = ans + q
			q = q*den
			num = num - q
		return ans
	@staticmethod
	def byroot(root):
		ans = Poly([1,-root[0]])
		for i in root[1:]:
			ans= ans*Poly([1,-i])
		return ans
def galoi(a):
	print('-->',a)
	if a == 256 :
		print('   <',29)
		return 29
	if a>256:
		a = 2*galoi(a//2)
		if a>=256:
			print('   <^',a^285)
			return a^285
	
	print('   <',a)
	return a

#print('\n'.join([f'{i+1} = 2^{l[i]} ' for i in range(len(l))]))
print(Poly([1,3.7,0]))