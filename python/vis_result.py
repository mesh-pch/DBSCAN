import os
import matplotlib.pyplot as plt

def read_data(file_name):
    data_set_x = list()
    data_set_y = list()
    cluter_id = -1
    with open(file_name, 'r') as f:
        line = f.readline()
        while line:
            if '@@##@@'==line.strip():
                cluter_id += 1
                data_set_x.append(list())
                data_set_y.append(list())
                line = f.readline()
                continue
            items = line.split()
            data_set_x[cluter_id].append(float(items[0]))
            data_set_y[cluter_id].append(float(items[1]))
            line = f.readline()
    return data_set_x, data_set_y
def read_origin(file_name):
    data_set_x = list()
    data_set_y = list()
    with open(file_name, mode='r') as f:
        line = f.readline()
        while line:
            items = line.split()
            data_set_x.append(float(items[0]))
            data_set_y.append(float(items[1]))
            line = f.readline()
    return data_set_x, data_set_y


if __name__ == '__main__':
    pwd = os.getcwd()
    file_name = os.path.join(pwd, '..', 'dataset/dbscan-res.pts')
    file_name_origin = os.path.join(pwd, '..',"dataset/test_data.pts")
    data_set_x, data_set_y = read_data(file_name)
    data_set_origin_x, data_set_origin_y = read_origin(file_name_origin)
    plt.figure(figsize=(1,2))
    plt.subplot(1,2,1)
    plt.plot(data_set_x[0], data_set_y[0],'ro')
    plt.plot(data_set_x[1], data_set_y[1],'go')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('dbscan')
    plt.subplot(1,2,2)
    plt.plot(data_set_origin_x, data_set_origin_y,'b*')

    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('origin')
    plt.show()