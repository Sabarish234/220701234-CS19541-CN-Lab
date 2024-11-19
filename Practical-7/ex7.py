import os

def create_frames(message):
    frames = []
    for i, char in enumerate(message):
        frames.append({'Frame_No': i, 'DATA': char})
    return frames

def sender(frames, window_size, start_frame):
    sent_frames = []
    for i in range(start_frame, len(frames), window_size):
        window_frames = frames[i:i+window_size]
        print(f"Sent frames: {window_frames}")
        sent_frames.extend(window_frames)
        
        # Save sent frames to Sender_Buffer.txt
        with open('Sender_Buffer.txt', 'w') as sender_file:
            for frame in window_frames:
                sender_file.write(f"{frame['Frame_No']} {frame['DATA']}\n")
        
        # Save received frames to Receiver_Buffer.txt under sender function
        with open('Receiver_Buffer.txt', 'w') as receiver_file:
            for frame in window_frames:
                receiver_file.write(f"{frame['Frame_No']}\n")
        
        save_last_frame(window_frames[-1]['Frame_No'])
        
        input("Press Enter to run the receiver...")  # Wait for Enter key press to proceed
        if not receiver():
            print("NACK received: Frame mismatch de+tected.")
        
        break  # Exit after sending one window worth of frames
    return sent_frames

def receiver():
    with open('Sender_Buffer.txt', 'r') as sender_file:
        sender_frames = [line.split()[0] for line in sender_file.readlines()]
    
    with open('Receiver_Buffer.txt', 'r') as receiver_file:
        receiver_frames = [line.strip() for line in receiver_file.readlines()]
    
    if sender_frames != receiver_frames:
        return False  # NACK condition: frames do not match
    else:
        print("Frames received correctly, sending ACKs\n")
        return True  # ACK condition: frames match

def save_last_frame(last_frame_no):
    with open('Last_Frame.txt', 'w') as f:
        f.write(str(last_frame_no))

def load_last_frame():
    if os.path.exists('Last_Frame.txt'):
        with open('Last_Frame.txt', 'r') as f:
            content = f.read().strip()
            if content.isdigit():
                return int(content) + 1
    return 0

def main():
    window_size = int(input("Enter window size: "))
    message = input("Enter text message: ")

    frames = create_frames(message)
    start_frame = load_last_frame()

    sender(frames, window_size, start_frame)

if __name__ == "__main__":
    main()
