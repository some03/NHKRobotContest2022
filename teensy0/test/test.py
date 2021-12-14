import math


def test():
    m=[0]*4
    theta=math.pi/2
    vx=10
    vy=10
    a=4
    m[0]=vx*math.cos((math.pi/a)+theta)-vy*math.sin(math.pi/a+theta);
    m[1]=-vx*math.cos((math.pi/a)-theta)-vy*math.sin(math.pi/a-theta);
    m[2]=-vx*math.cos((math.pi/a)+theta)+vy*math.sin(math.pi/a+theta);
    m[3]=vx*math.cos((math.pi/a)-theta)+vy*math.sin(math.pi/a-theta);
    print(m[0])
    print(m[1])
    print(m[2])
    print(m[3])
test()
