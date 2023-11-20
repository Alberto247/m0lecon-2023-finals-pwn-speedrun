import subprocess


print(subprocess.check_output(["wget", "https://webhook.site/85ed6a3a-e72d-49d3-ac67-672ece7148e1", "--post-data", b"\x01\x02"]))