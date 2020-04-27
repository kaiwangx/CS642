# import hashlib
#
# notFound = 1
# digit = 1
# while notFound:
#     print(digit)
#     for x in range(0, pow(10, digit)):
#         password = str(x)
#         if x < pow(10, digit - 1):
#             password = password.rjust(digit, '0')
#         if hashlib.sha256(("bucky," + password + ",20200128").encode()).hexdigest() == \
#                 "61ef437ca1493baf5ce815a8ca13ec1fba31645f7d85edebac7c60e0aa98b5c6":
#             print(password)
#             notFound = 0
#             break
#     digit += 1

# print(x)
#
# print(hashlib.sha256("bucky,11235813,20200128".encode()).hexdigest())

