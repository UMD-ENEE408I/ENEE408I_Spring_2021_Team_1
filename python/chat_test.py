from chat_client import RobotChatClient
import time

username = 'Suyaib'

def test_callback(message_dict):
    
    if message_dict['type'] == 'message':
        print('{0} : {1}'.format(message_dict['user'],message_dict['message']))

    if message_dict['type'] == 'users':
        print('Number of users: {}'.format(message_dict['count']))

# Run this script directly to invoke this test sequence
if __name__ == '__main__':
    print('Creating RobotChatClient object')
    client = RobotChatClient('ws://something.ngrok.io', callback=test_callback)

    time.sleep(1)

    print('User Joined: Suyaib Has Connected')
    client.send({'type': 'message',
                 'user': 'User Joined',
                 'message': 'Suyaib'})

    string = input()
    while(string != 'quit'):
        client.send({'type': 'message', 'user': username, 'message': string})
        string = input()

    client.send({'type': 'message',
                 'user': 'User Disconnected',
                 'message': 'Suyaib'})

    print("please use ctrl + c to end the program")