# LaZyDev C Library


### System Export Value

* You need to export LZLIB_HOME(the working directory) to .bash_profile or equivaluent.

  example: in .bash_profile

  `export LZLIB_HOME=~/work/lzlib`

---------------------------------------------------------------------------------------


### Components List

* lz_typeconv
  - type conversion component

* lz_datetime
  - datetime component
  - dependency : lz_typeconv

* lz_logger
  - logger component
  - dependency : lz_typeconv, lz_datetime

* lz_hashmap
  - hashmap component

### Flask Instance Folders
---
<br>

OS는 각각의 프로세스들의 working directory들을 알고 있다. 하지만 Web-Application에서는 하나의 프로세스안에 여러개의 Application들을 가질 가능성이 있다. Flask에서는 app.root_path와 os.path를 이용하여 원하는 파일을 찾을 수 있지만 Application이 package일 경우 root_path는 package의 contents를 바라보기 때문에 올바르게 작동하지 않는다.

이런 이유로 Flask 0.8에서 **flask.instance_path**라는 새로운 attribute를 추가하였다. 이 속성은 Instance Folders라는 새로운 개념을 이용한다. Instance Folders는 version control안에 있지 않고 Deployment Specific이다. 그러므로 이 폴더가 config/설정 파일들을 넣기에는 최적의 장소이다.
<br>




```Python
app = Flask(__name__, instance_path='/path/to/instance/folder')
```
여기서 instance_path에 지정하는 path는 Absolute path이다. instance_path가 주어지지 않았다면 아래의 default 폴더가 사용된다.

* Uninstalled module
```Python
/app.py
/instance
```

* Uninstalled package
```Python
/myapp
  /__init__.py
/instance
```

* Installed module or package
```Python
$PREFIX/lib/python2.X/site-packages/myapp
$PREFIX/var/myapp-instance
```
$PREFIX는 Python 설치 폴더이다.

Flask에서는 보통 config 파일에서 config object를 load하므로 instance 폴더의 위치의 상관없이 instance 폴더안의 config 파일을 load할 수 있게 있다. (default는 application root 폴더를 보고 있다.)
예를 들면 Uninstalled package가 아래와 같이 있다고 할 때
```Python
/myapp
  /__init__.py
/instance
```

**A**
```Python
app = Flask(__name__)
app.config.from_pyfile('application.cfg', silent=True)
```

**B**
```Python
app = Flask(__name__, instance_relative_config=True)
app.config.from_pyfile('application.cfg', silent=True)
```

위의 A에서는 default가 application root 폴더이므로 /myapp 폴더안에서 application.cfg를 찾을 것이며, B에서는 instance_relative_config를 True로 설정하므로 instance 폴더가 어디에 있든지 instance 폴더안에서 application.cfg에서 찾을 것이다. **silent=True**는 해당 폴더에 application.cfg파일이 없어도 complain하지 말고 조용히 있으라는 설정이다.
