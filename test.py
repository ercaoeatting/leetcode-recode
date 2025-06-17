import asyncio
import websockets
import json
import time

async def websocket_client():
    uri = "ws://localhost:9002"
    
    async with websockets.connect(uri) as websocket:
        # 首次连接认证
        auth = json.dumps({"action": "auth", "token": "your_token"}, ensure_ascii=False)
        await websocket.send(auth)
        i = 0
        while True:
            i += 1
            await asyncio.sleep(1)
            print(f"发送消息 {i}...")
            # 构造中文消息（确保不转码）
            msg = json.dumps({
                "seq": i,
                "time": time.strftime("%H:%M:%S"),
            }, ensure_ascii=False)
            
            await websocket.send(msg)
            print(f"📤 发送: {msg}")
            
            try:
                response = await asyncio.wait_for(websocket.recv(), timeout=1)
                try:
                    # 尝试解析并美化打印JSON
                    parsed = json.loads(response)
                    print(f"📥 收到: {json.dumps(parsed, indent=2, ensure_ascii=False)}")
                except:
                    print(f"📥 收到: {response}")
            except asyncio.TimeoutError:
                print("⏱️ 响应超时")

asyncio.run(websocket_client())