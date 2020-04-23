from console import *
from service import *
from repository import *

repo = Repository("input.txt")
service = Service(repo)
console = Console(service)

console.run()