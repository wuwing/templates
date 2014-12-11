#sort
students = [('join','A',15),('jane','8',12),('dave','8',10)]

sorted(students,key = lambda student:student[2])

sorted(students,key = lambda student:student.age)

from operator import itemgetter,attrgetter
sorted(students,key = itemgetter(2))
sorted(students,key = attrgetter('age'))

sorted(students,key = itemgetter(1,2))
sorted(students,key = key = attrgetter('grade','age'))

d = {'a':2, 'b':23, 'c':5, 'd':17, 'e':1}
from operator import itemgetter
sorted(d.iteritems(),key = itemgetter(1), reverse = True)

sorted(d.key = d.__getitem, reverse = True)

list.sort()
