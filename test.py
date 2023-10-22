import pandas as pd
import matplotlib.pyplot as plt

pd.set_option("display.max.columns", None)

#don't show specific columns
col_to_skip = ['owner-id', 'network-id', 'date', 'utc-offset', 'start-ime', 'end-time', 'device-id', 'detector-type', 'sample-period', 'cst-time', 'month', 'day']

'''d1 = pd.read_csv('csv_files/Wavetronix pg69.csv', usecols=lambda x: x not in col_to_skip)
d2 = pd.read_csv('csv_files/Wavetronix pg70.csv', usecols=lambda x: x not in col_to_skip)

data = d1.merge(d2, how='outer')'''

data = pd.read_csv("datav1/sample_data.csv", usecols=lambda x: x not in col_to_skip)

data = data.drop(data[data['status'] != 'OK'].index)
data = data.drop(data[data['device-description'] != 'NORMAL'].index)

truck_array = []
control_array = []
total_array = []


for index, row in data.iterrows():
    
    if (index+2 != len(data)):
        prev = data.iloc[index]
        cur = data.iloc[index+1]
        ahead = data.iloc[index+2]

        cur_total_small = cur['small-class-count']# + cur['medium-class-count']
        prev_total_small = prev['small-class-count']# + prev['medium-class-count']
        ahead_total_small = ahead['small-class-count']# + ahead['medium-class-count']
        #put back medium if broke
        if (cur['small-class-count'] + cur['medium-class-count'] + cur['large-class-count'] != 0):
            
            if (prev['lane-id'] > cur['lane-id'] or prev['lane-id'] == 0):
                #don't count prev, compare cur to ahead
                if (cur_total_small > 0 and ahead['large-class-count'] > 0 and cur['large-class-count'] == 0):
                    truck_array.append(cur['lane-speed'])
                    total_array.append(cur['lane-speed'])
                elif (cur_total_small > 0 and ahead['large-class-count'] == 0 and cur['large-class-count'] == 0):
                    control_array.append(cur['lane-speed'])
                    total_array.append(cur['lane-speed'])

            elif (prev['lane-id'] < cur['lane-id'] and cur['lane-id'] < ahead['lane-id']):
                #compre to prev and ahead
                if prev['large-class-count'] > 0 or ahead['large-class-count'] > 0 and cur['large-class-count'] == 0:
                    truck_array.append(cur['lane-speed'])
                    total_array.append(cur['lane-speed'])

                elif (cur_total_small > 0 and prev['large-class-count'] == 0 and ahead['large-class-count'] == 0 and cur['large-class-count'] == 0):
                    control_array.append(cur['lane-speed'])
                    total_array.append(cur['lane-speed'])
                    
            elif (prev['lane-id'] < cur['lane-id'] and ahead['lane-id'] < cur['lane-id']):
                #compre cur to prev
                if (prev['large-class-count'] > 0 and cur['large-class-count'] == 0):
                    truck_array.append(cur['lane-speed'])
                    total_array.append(cur['lane-speed'])

                elif (prev['large-class-count'] == 0 and cur_total_small > 0):
                    control_array.append(cur['lane-speed'])
                    total_array.append(cur['lane-speed'])

            elif (prev['link-direction'] != cur['link-direction'] and cur['link-direction'] != ahead['link-direction']):
                #1 lane
                if (cur['large-class-count'] == 0 and cur_total_small > 0):
                    control_array.append(cur['lane-speed'])
                    total_array.append(cur['lane-speed'])

            elif (prev['lane-id'] < cur['lane-id'] and ahead['link-direction'] != cur['link-direction']):
                #compare prev to cur
                if (cur['large-class-count'] > 0 and prev['small-class-count'] > 0):
                    truck_array.append(cur['lane-speed'])
                    total_array.append(cur['lane-speed'])

                elif (cur['large-class-count'] == 0 and prev['small-class-count'] > 0 and prev['large-class-count'] == 0):
                    control_array.append(cur['lane-speed'])
                    total_array.append(cur['lane-speed'])

    else:
        #will end 2 short which is within a certain margine of error that won't affect our over all data in a significant margin
        break

avg_truck_array_speed = sum(truck_array) / len(truck_array)
avg_control_array_speed = sum(control_array) / len(control_array)
avg_total_array_speed = sum(total_array) / len(total_array)

print("Total Array avg speed: ", avg_total_array_speed)
print("Truck Array avg speed: ", avg_truck_array_speed)
print("Control Array avg speed: ", avg_control_array_speed)

#Graph
plt.bar(['Control', 'Average', 'Truck'], [avg_control_array_speed, avg_total_array_speed, avg_truck_array_speed])
plt.xlabel('Truck vs Control')
plt.ylabel('Average Speed')
plt.title('Truck vs Control Average Speed')
plt.show()


#Life can get busy when there are cursors all over your screen
#Come to the cursor parking lot to clear your mind and window
"""
----------------------------------------------
|                                               
|                                               
|           Cursor Parking Lot                  
|                                               
|                                               
|                                                   
|                                               
----------------------------------------------
"""