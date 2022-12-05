from cvxopt.modeling import variable, op


x = variable(25, 'x')

z = (1 * x[0]	+	5 * x[1]	+	7 * x[2]	+	9 * x[3]	+	3 * x[4]	+	
     4 * x[2]	+	6 * x[3]	+	4 * x[4]	+	7 * x[5]	+	13 * x[6]	+	
     1 * x[6]	+	5 * x[7]	+	3 * x[8]	+	4 * x[9]	+	9 * x[10]	+	
     2 * x[12]	+	4 * x[13]	+	2 * x[14]	+	10 * x[15]	+	3 * x[16]	+	
     3 * x[20]	+	2 * x[21]	+	5 * x[22]	+	6 * x[23]	+	4 * x[24]	)

mass0 = (x[0]	+	x[1]	+	x[2]	+	x[3]	+	x[4]	<= 10)
mass1 = (x[5]	+	x[6]	+	x[7]	+	x[8]	+	x[9]	<= 10)
mass2 = (x[10]	+	x[11]	+	x[12]	+	x[13]	+	x[14]	<= 25)
mass3 = (x[15]	+	x[16]	+	x[17]	+	x[18]	+	x[19]	<= 25)
mass4 = (x[20]	+	x[21]	+	x[22]	+	x[23]	+	x[24]	<= 30)

mass5 = (x[0]	+	x[5]	+	x[10]	+	x[15]	+	x[20]	== 10)
mass6 = (x[1]	+	x[6]	+	x[11]	+	x[16]	+	x[21]	== 20)
mass7 = (x[2]	+	x[7]	+	x[12]	+	x[17]	+	x[22]	== 10)
mass8 = (x[3]	+	x[8]	+	x[13]	+	x[18]	+	x[23]	== 30)
mass9 = (x[4]	+	x[9]	+	x[14]	+	x[19]	+	x[24]	== 10)

x_non_negative = (x>=0)

problem = op(z,[mass0, mass1, mass2, mass3, mass4, mass5, mass6, mass7, mass8, mass9, x_non_negative])

problem.solve(solver="glpk")
problem.status
print("Result: {}".format(x.value))
print("Price: {}".format(problem.objective.value()[0]))